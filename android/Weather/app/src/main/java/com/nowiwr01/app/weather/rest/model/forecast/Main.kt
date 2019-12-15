package com.nowiwr01.app.weather.rest.model.forecast

import com.google.gson.annotations.SerializedName

data class Main(
    val temp: Double = 0.0,
    @SerializedName("temp_min")
    val tempMin: Double = 0.0,
    @SerializedName("grnd_level")
    val grndLevel: Double = 0.0,
    @SerializedName("temp_kf")
    val tempKf: Double = 0.0,
    val humidity: Int = 0,
    val pressure: Double = 0.0,
    @SerializedName("sea_level")
    val seaLevel: Double = 0.0,
    @SerializedName("temp_max")
    val tempMax: Double = 0.0
)