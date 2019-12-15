package com.nowiwr01.app.weather.presenters

import com.nowiwr01.app.weather.rest.model.current.CurrentWeatherModel
import com.nowiwr01.app.weather.rest.model.forecast.ForecastWeatherModel

interface WeatherContract {

    interface BaseContract {
        fun showProgress()
        fun hideProgress()
        fun showError()
    }

    interface HomeContract : BaseContract {
        fun updateWeather(modelCurrent: CurrentWeatherModel)
        fun addDay(modelForecast: ForecastWeatherModel)
    }

    interface HourlyForecastContract: BaseContract {
        fun addHour(forecastWeatherModel: ForecastWeatherModel)
        fun setTimezone(timezone: Long)
    }
}
