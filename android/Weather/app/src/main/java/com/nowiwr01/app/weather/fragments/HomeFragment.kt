package com.nowiwr01.app.weather.fragments

import android.annotation.SuppressLint
import android.os.Bundle
import androidx.recyclerview.widget.LinearLayoutManager
import kotlinx.android.synthetic.main.fragment_home.*
import kotlinx.android.synthetic.main.item_progress.*
import com.nowiwr01.app.weather.R
import com.nowiwr01.app.weather.utils.Utils
import com.nowiwr01.app.weather.adapters.DailyForecastAdapter
import com.nowiwr01.app.weather.adapters.model.DailyForecast
import com.nowiwr01.app.weather.presenters.HomePresenter
import com.nowiwr01.app.weather.rest.model.current.CurrentWeatherModel
import com.nowiwr01.app.weather.rest.model.forecast.ForecastWeatherModel
import android.view.*
import androidx.recyclerview.widget.RecyclerView
import com.google.android.material.snackbar.Snackbar
import com.nowiwr01.app.weather.adapters.BaseAdapterCallback
import com.nowiwr01.app.weather.presenters.WeatherContract
import java.util.*

class HomeFragment : BaseFragment(), WeatherContract.HomeContract {

    companion object {
        fun newInstance(): HomeFragment {
            return HomeFragment()
        }
    }

    private var timezoneOffset: Long = 0
    private var currentCity: String = ""
    private lateinit var views: List<View>
    private lateinit var recyclerView: RecyclerView
    private lateinit var presenter: HomePresenter
    private lateinit var viewAdapter: DailyForecastAdapter

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        retainInstance = true
        setHasOptionsMenu(true)
    }

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        return inflater.inflate(R.layout.fragment_home, container, false)
    }

    @ExperimentalStdlibApi
    override fun onRefresh() {
        super.onRefresh()
        viewAdapter.clearItems()
        viewAdapter.notifyDataSetChanged()
        presenter.loadWeatherByCity("Los Angeles")
    }

    @ExperimentalStdlibApi
    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        presenter = HomePresenter()
        presenter.attach(this)

        viewAdapter = DailyForecastAdapter()
        viewAdapter.attachCallback(object: BaseAdapterCallback<DailyForecast> {
            override fun onItemClick(model: DailyForecast, view: View) {
                val currentFragment = activity!!.supportFragmentManager.fragments.last()
                activity!!.supportFragmentManager.beginTransaction()
                    .hide(currentFragment)
                    .add(R.id.container, HourlyForecastFragment.newInstance(model.day, currentCity), null)
                    .addToBackStack(null)
                    .commit()
            }
        })

        recyclerView = dailyForecastList.apply {
            layoutManager = LinearLayoutManager(context, LinearLayoutManager.HORIZONTAL, false)
            isNestedScrollingEnabled = false
            adapter = viewAdapter
        }

        views = listOf<View>(
            temperature, weather_condition_text_view, humadity, wind, drop, flag
        )

        presenter.loadWeatherByCity("Singapore")

    }

    private fun setVisibility(visibility: Int) {
        for (view in views) {
            view.visibility = visibility
        }
    }

    override fun showProgress() {
        setVisibility(View.GONE)
        progress.visibility = View.GONE
    }

    override fun hideProgress() {
        setVisibility(View.VISIBLE)
        progress.visibility = View.GONE
    }

    override fun showError() {
        progress.visibility = View.GONE
        Snackbar.make(coordinator_layout, "Что-то пошло не так", Snackbar.LENGTH_LONG).show()
    }

    @SuppressLint("SetTextI18n")
    @ExperimentalStdlibApi
    override fun updateWeather(modelCurrent: CurrentWeatherModel) {
        city.text = "${modelCurrent.name}, ${modelCurrent.sys.country}"
        wind.text = "${modelCurrent.wind.speed} м/c"
        icon.setImageResource(Utils.getIconNameResource(modelCurrent.weather[0].icon))
        temperature.text = Utils.formatTemperature(modelCurrent.main.temp)
        weather_condition_text_view.text = modelCurrent.weather[0].description.capitalize(Locale.getDefault())
        humadity.text = "${modelCurrent.main.humidity} %"
        timezoneOffset = modelCurrent.timezone
        currentCity = modelCurrent.name
    }

    override fun addDay(modelForecast: ForecastWeatherModel) {
        val dt = modelForecast.dt + timezoneOffset

        val dayForecast = DailyForecast(
            Utils.getIconNameResource(modelForecast.weather[0].icon),
            Utils.getDateTime(dt, "dd"),
            Utils.getDateTime(dt, "E"),
            "${modelForecast.wind.speed.toInt()} м/c",
            modelForecast.weather[0].description,
            Utils.formatTemperature(modelForecast.main.temp))

        viewAdapter.addItem(dayForecast)
    }

    override fun onResume() {
        super.onResume()
        presenter.attach(this)
    }

    override fun onPause() {
        super.onPause()
        presenter.detach()
    }
}