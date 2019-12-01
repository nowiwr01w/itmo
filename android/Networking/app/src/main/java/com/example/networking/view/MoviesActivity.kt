package com.example.networking.view

import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.content.IntentFilter
import android.graphics.BitmapFactory
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import androidx.localbroadcastmanager.content.LocalBroadcastManager
import com.example.networking.R
import com.example.networking.services.MoviesService
import com.example.networking.services.MoviesService.Companion.BYTE_ARRAY_TAG
import com.example.networking.services.MoviesService.Companion.RESPONSE_TAG
import kotlinx.android.synthetic.main.activity_movies.*

class MoviesActivity : AppCompatActivity() {

    private var myBroadCastReceiver: BroadcastReceiver? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_movies)

        startService(Intent(this, MoviesService::class.java).apply {
            putExtra(PICTURE_TAG, intent.getStringExtra(PICTURE_TAG))
        })

        film_name.text = intent.getStringExtra(TITLE_TAG)
        year.text = intent.getStringExtra(YEAR_TAG)

        myBroadCastReceiver = object : BroadcastReceiver() {
            override fun onReceive(context: Context?, intent: Intent?) {
                val byteArray = intent?.getByteArrayExtra(BYTE_ARRAY_TAG)
                if (byteArray != null) {
                    val byteImage = BitmapFactory.decodeByteArray(byteArray, 0, byteArray.size)
                    picture.setImageBitmap(byteImage)
                }
            }
        }

        LocalBroadcastManager.getInstance(this).registerReceiver(myBroadCastReceiver as BroadcastReceiver,
            IntentFilter(RESPONSE_TAG).apply {
                addCategory(Intent.CATEGORY_DEFAULT)
        })
    }

    override fun onDestroy() {
        super.onDestroy()
        LocalBroadcastManager.getInstance(this).unregisterReceiver(myBroadCastReceiver!!)
    }

    companion object {
        const val YEAR_TAG = "year"
        const val TITLE_TAG = "title"
        const val PICTURE_TAG = "picture"
    }
}
