package com.nowiwr01.app.weather.rest.model.forecast

data class City(
    val id: Long = 0,
    val name: String = "",
    val coord: Coord,
    val country: String = "",
    val timezone: Long = 0
)