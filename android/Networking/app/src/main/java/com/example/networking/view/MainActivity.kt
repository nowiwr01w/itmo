package com.example.networking.view

import android.content.Intent
import android.content.res.Configuration
import android.os.AsyncTask
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.Menu
import android.view.MenuItem
import android.view.View
import androidx.recyclerview.widget.GridLayoutManager
import com.example.networking.R
import com.example.networking.adapters.MovieAdapter
import com.example.networking.model.Movie
import kotlinx.android.synthetic.main.activity_main.*
import org.json.JSONArray
import org.json.JSONException
import org.json.JSONObject
import java.lang.ref.WeakReference
import java.net.HttpURLConnection
import java.net.URL
import android.net.ConnectivityManager
import android.content.Context
import android.widget.Toast
import com.example.networking.BuildConfig
import com.example.networking.view.MoviesActivity.Companion.PICTURE_TAG
import com.example.networking.view.MoviesActivity.Companion.TITLE_TAG
import com.example.networking.view.MoviesActivity.Companion.YEAR_TAG
import androidx.appcompat.widget.SearchView as SearchView

@Suppress("DEPRECATION")
class MainActivity : AppCompatActivity() {

    private var lastRequest: String? = ""
    private var myAsyncTask: AsyncTaskHandlerJSON? = null

    private lateinit var movieAdapter: MovieAdapter

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        setSupportActionBar(toolbar)

        myAsyncTask = (lastCustomNonConfigurationInstance as? AsyncTaskHandlerJSON) ?: AsyncTaskHandlerJSON(this)
        myAsyncTask?.attachActivity(this)

        Log.d(LOG_TAG, "Create MainActivity: " + this@MainActivity.hashCode())
        Log.d(LOG_TAG, "Create AsyncTask: " + myAsyncTask.hashCode())
    }


    override fun onRetainCustomNonConfigurationInstance(): Any? =  myAsyncTask

    private fun isNetworkConnected(): Boolean {
        val cm = getSystemService(Context.CONNECTIVITY_SERVICE) as ConnectivityManager
        return cm.activeNetworkInfo != null && cm.activeNetworkInfo!!.isConnected
    }

    private fun attachList(curList: ArrayList<Movie>?) {
        if (curList != null) {
            movieAdapter = MovieAdapter(curList, applicationContext) { movie ->
                val intent = Intent(this, MoviesActivity::class.java).apply {
                    putExtra(YEAR_TAG, movie.year)
                    putExtra(TITLE_TAG, movie.title)
                    putExtra(PICTURE_TAG, movie.picture)
                }
                startActivity(intent)
            }

            movieRecyclerView.apply {
                setHasFixedSize(true)
                adapter = movieAdapter
                layoutManager = if (resources.configuration.orientation == Configuration.ORIENTATION_PORTRAIT) {
                    GridLayoutManager(applicationContext, 2)
                } else {
                    GridLayoutManager(applicationContext, 5)
                }
            }
        }
    }

    private fun downloadUsingAsyncTask(name: String?) {
        myAsyncTask?.activityReference = WeakReference(null)
        myAsyncTask = AsyncTaskHandlerJSON(this).apply {
            execute(url + (name ?: "superman") + "&page=")
            attachActivity(this@MainActivity)
        }
        Log.d(LOG_TAG, "Create MainActivity: " + this@MainActivity.hashCode())
        Log.d(LOG_TAG, "Create AsyncTask: " + myAsyncTask.hashCode())
    }

     private class AsyncTaskHandlerJSON(activity: MainActivity?) : AsyncTask<String, Int, ArrayList<Movie>>() {

        var activityReference = WeakReference(activity)
        private var cachedResult: ArrayList<Movie>? = null


        override fun doInBackground(vararg url: String?): ArrayList<Movie> {

            val movieList: ArrayList<Movie> = ArrayList()

            for (i in 1..10) {
                val text: String
                val connection = URL(url[0] + "$i").openConnection() as HttpURLConnection
                try {
                    connection.connect()
                    text = connection.inputStream.reader().readText()
                } finally {
                    connection.disconnect()
                }

                val jsonArray: JSONArray
                try {
                    jsonArray = JSONObject(text).getJSONArray("Search")
                } catch (e: JSONException) {
                    // Т.к. подгружаем первые 10 страниц, может не найтись столько фильмов по запросу.
                    // Например "Interstellar"
                    break
                }

                for (j in 0 until jsonArray.length()) {
                    val jsonObject = jsonArray.getJSONObject(j)
                    movieList.add(
                        Movie(
                            jsonObject.getString("Poster"),
                            jsonObject.getString("Title"),
                            jsonObject.getString("Year")
                        )
                    )
                    publishProgress(j + 10 * (i - 1))
                }
            }
            return movieList
        }

        override fun onProgressUpdate(vararg values: Int?) {
            super.onProgressUpdate(*values)
            activityReference.get()?.listProgressBar?.apply {
                max = 100
                progress = values[0]!!
                visibility = View.VISIBLE
            }
        }

        fun attachActivity(activity: MainActivity) {
            activityReference = WeakReference(activity)
            cachedResult?.let { movieList->
                activityReference.get()?.setMoviesInUI(movieList)
                cachedResult = null
            }
        }

        override fun onPostExecute(jsonList: ArrayList<Movie>?) {
            super.onPostExecute(jsonList)
            activityReference.get()?.listProgressBar?.visibility = View.GONE
            activityReference.get()?.setMoviesInUI(jsonList) ?: run {
                cachedResult = jsonList
            }
        }
    }

    private fun setMoviesInUI(curList: ArrayList<Movie>?) {
        if (curList != null) {
            attachList(curList)
        }
        myAsyncTask = null
    }

    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        menuInflater.inflate(R.menu.menu, menu)
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        when (item.itemId) {
            R.id.searchToolbar -> doSearch(item)
            else -> super.onOptionsItemSelected(item)
        }
        return true
    }

    private fun doSearch(menuItem: MenuItem) {
        val searchView: SearchView = menuItem.actionView as SearchView

        searchView.queryHint = "Type here to Search"
        searchView.setOnQueryTextListener(object : SearchView.OnQueryTextListener {

            override fun onQueryTextSubmit(curRequest: String?): Boolean {
                lastRequest = curRequest
                movieRecyclerView.adapter = MovieAdapter(arrayListOf(), applicationContext) {}
                if (isNetworkConnected()) {
                    downloadUsingAsyncTask(curRequest)
                } else {
                    Toast.makeText(applicationContext, "No internet", Toast.LENGTH_LONG).show()
                }
                menuItem.collapseActionView()
                return false
            }

            override fun onQueryTextChange(prefix: String?): Boolean = false
        })
    }

    override fun onSaveInstanceState(outState: Bundle) {
        super.onSaveInstanceState(outState)
        outState.putString(URL_TAG, lastRequest)
    }

    override fun onRestoreInstanceState(savedInstanceState: Bundle) {
        super.onRestoreInstanceState(savedInstanceState)
        lastRequest = savedInstanceState.getString(URL_TAG)
        downloadUsingAsyncTask(lastRequest)
    }

    override fun onDestroy() {
        myAsyncTask?.activityReference = WeakReference(null)
        super.onDestroy()
    }

    companion object {
        private const val LOG_TAG = "THREADS"
        private const val URL_TAG = "lastRequest"

        private const val url = "http://www.omdbapi.com/?apikey=${BuildConfig.APIKEY}&s="
    }
}
