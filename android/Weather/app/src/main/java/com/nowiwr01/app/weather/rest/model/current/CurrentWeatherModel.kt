package com.nowiwr01.app.weather.rest.model.current

data class CurrentWeatherModel(
    val dt: Long = 0,
    val timezone: Long = 0,
    val coord: Coord,
    val visibility: Int = 0,
    val weather: List<WeatherItem>,
    val name: String = "",
    val cod: Int = 0,
    val main: Main,
    val clouds: Clouds,
    val id: Int = 0,
    val sys: Sys,
    val base: String = "",
    val wind: Wind
)