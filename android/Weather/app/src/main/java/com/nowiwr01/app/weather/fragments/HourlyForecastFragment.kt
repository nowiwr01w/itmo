package com.nowiwr01.app.weather.fragments

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import kotlinx.android.synthetic.main.fragment_hourly_forecast.*
import kotlinx.android.synthetic.main.item_progress.*
import com.nowiwr01.app.weather.R
import com.nowiwr01.app.weather.utils.Utils
import com.nowiwr01.app.weather.adapters.BaseAdapter
import com.nowiwr01.app.weather.adapters.HourlyForecastAdapter
import com.nowiwr01.app.weather.adapters.model.HourlyForecast
import com.nowiwr01.app.weather.presenters.HourlyForecastPresenter
import com.nowiwr01.app.weather.presenters.WeatherContract
import com.nowiwr01.app.weather.rest.model.forecast.ForecastWeatherModel
import java.util.*

class HourlyForecastFragment : BaseListFragment<HourlyForecast>(), WeatherContract.HourlyForecastContract {

    private lateinit var presenter: HourlyForecastPresenter
    private val day: String
        get() = arguments!!.getString(DAY, "")

    private val city: String
        get() = arguments!!.getString(CITY, "")

    private var timezoneOffset: Long = 0

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        return inflater.inflate(R.layout.fragment_hourly_forecast, container, false)
    }

    @ExperimentalStdlibApi
    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        presenter = HourlyForecastPresenter()
        presenter.attach(this)
        presenter.loadForecastForDayByCity(day, city)
    }

    override fun onResume() {
        super.onResume()
        presenter.attach(this)
    }

    override fun onPause() {
        super.onPause()
        presenter.detach()
    }

    @ExperimentalStdlibApi
    override fun onRefresh() {
        super.onRefresh()
        viewAdapter.clearItems()
        viewAdapter.notifyDataSetChanged()
        presenter.loadForecastForDayByCity(day, city)
    }

    override fun showProgress() {
        progress.visibility = View.VISIBLE
        list.visibility = View.GONE
        error.visibility = View.GONE
    }

    override fun hideProgress() {
        progress.visibility = View.GONE
        list.visibility = View.VISIBLE
        error.visibility = View.GONE
    }

    override fun showError() {
        progress.visibility = View.GONE
        list.visibility = View.GONE
        error.visibility = View.VISIBLE
    }

    override fun createAdapterInstance(): BaseAdapter<HourlyForecast> {
        return HourlyForecastAdapter()
    }

    @ExperimentalStdlibApi
    override fun addHour(forecastWeatherModel: ForecastWeatherModel) {
        val dt = forecastWeatherModel.dt + timezoneOffset

        val hourlyForecast = HourlyForecast(
            Utils.getIconNameResource(forecastWeatherModel.weather[0].icon),
            Utils.getDateTime(dt, "EEEE, HH:mm"),
            "${forecastWeatherModel.weather[0].description.capitalize(Locale.getDefault())}, влажность ${forecastWeatherModel.main.humidity} %",
            Utils.formatTemperature(forecastWeatherModel.main.tempMin),
            Utils.formatTemperature(forecastWeatherModel.main.tempMax))

        viewAdapter.addItem(hourlyForecast)

    }

    override fun setTimezone(timezone: Long) {
        timezoneOffset = timezone
    }

    companion object {
        const val DAY = "day"
        const val CITY = "city"

        fun newInstance(day: String, city: String): HourlyForecastFragment {
            val bundle = Bundle()
            val fragment = HourlyForecastFragment()

            bundle.putString(DAY, day)
            bundle.putString(CITY, city)

            fragment.arguments = bundle
            return fragment
        }
    }
}