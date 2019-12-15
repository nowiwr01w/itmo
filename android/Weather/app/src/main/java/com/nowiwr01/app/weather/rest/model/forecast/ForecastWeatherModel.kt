package com.nowiwr01.app.weather.rest.model.forecast

import com.google.gson.annotations.SerializedName

data class ForecastWeatherModel(
    val dt: Long = 0,
    @SerializedName("dt_txt")
    val dtTxt: String = "",
    val weather: List<WeatherItem>,
    val main: Main,
    val clouds: Clouds,
    val sys: Sys,
    val wind: Wind
)