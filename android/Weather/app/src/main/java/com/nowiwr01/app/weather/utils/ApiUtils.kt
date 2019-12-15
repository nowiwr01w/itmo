package com.nowiwr01.app.weather.utils

import com.nowiwr01.app.weather.rest.WeatherApi

class ApiUtils {

    companion object {
        const val BASE_URL = "https://api.openweathermap.org/data/2.5/"
        const val API_KEY = "c91a4f58f2f6d9e7e745e09ee4fdd5b0"

        val weatherApi: WeatherApi by lazy {
            WeatherApi.create()
        }
    }
}