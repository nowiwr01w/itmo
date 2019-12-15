package com.nowiwr01.app.weather.utils

import com.nowiwr01.app.weather.R
import java.text.SimpleDateFormat
import java.util.*

class Utils {

    companion object {

        fun getDateTime(dt: Long, pattern: String = "dd.MM.yyyy HH:mm:ss"): String {
            val date = Date(dt * 1000)
            val sdf = SimpleDateFormat(pattern, Locale.US)
            sdf.timeZone = TimeZone.getTimeZone("UTC")
            return sdf.format(date)
        }

        fun getHours(dt: Long): Int {
            val date = Date(dt * 1000)
            val sdf = SimpleDateFormat("HH", Locale.US)
            sdf.timeZone = TimeZone.getTimeZone("UTC")
            return sdf.format(date).toInt()
        }

        fun formatTemperature(temperature: Double): String {
            val value = (temperature - 273.15).toInt()
            return "$value°"
        }

        fun getIconNameResource(name: String) = when (name) {
            "01d" -> R.drawable.ic_1
            "01n" -> R.drawable.ic_33
            "02d" -> R.drawable.ic_20
            "02n" -> R.drawable.ic_35
            "03d" -> R.drawable.ic_20
            "03n" -> R.drawable.ic_brightness
            "04d" -> R.drawable.ic_20
            "04n" -> R.drawable.ic_brightness
            "09d" -> R.drawable.ic_12
            "09n" -> R.drawable.ic_41
            "10d" -> R.drawable.ic_18
            "10n" -> R.drawable.ic_18
            "11d" -> R.drawable.ic_41
            "11n" -> R.drawable.ic_41
            "13d" -> R.drawable.ic_22
            "13n" -> R.drawable.ic_32
            "50d" -> R.drawable.ic_8
            "50n" -> R.drawable.ic_8
            else -> R.drawable.ic_launcher_background
        }
    }
}