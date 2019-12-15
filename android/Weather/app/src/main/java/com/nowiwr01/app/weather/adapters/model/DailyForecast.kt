package com.nowiwr01.app.weather.adapters.model

data class DailyForecast(
    val icon: Int,
    val day: String,
    val date: String,
    val wind: String,
    val description: String,
    val temperature: String
)