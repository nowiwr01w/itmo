package com.nowiwr01.app.weather.adapters.model

data class HourlyForecast(
    val icon: Int,
    val datetime: String,
    val description: String,
    val lowTemp: String,
    val highTemp: String
)