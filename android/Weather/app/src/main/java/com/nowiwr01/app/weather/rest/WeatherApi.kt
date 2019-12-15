package com.nowiwr01.app.weather.rest

import io.reactivex.Observable
import retrofit2.Retrofit
import retrofit2.adapter.rxjava2.RxJava2CallAdapterFactory
import retrofit2.converter.gson.GsonConverterFactory
import retrofit2.http.GET
import retrofit2.http.Query
import com.nowiwr01.app.weather.utils.ApiUtils.Companion.API_KEY
import com.nowiwr01.app.weather.utils.ApiUtils.Companion.BASE_URL
import com.nowiwr01.app.weather.rest.model.current.CurrentWeatherModel
import com.nowiwr01.app.weather.rest.model.forecast.ForecastList

interface WeatherApi {

    @GET("weather")
    fun getWeatherByCity(@Query("q") city: String,
                         @Query("appid") apiKey: String = API_KEY,
                         @Query("lang") lang: String = "ru"): Observable<CurrentWeatherModel>


    @GET("forecast")
    fun getForecastByCity(@Query("q") city: String,
                          @Query("appid") apiKey: String = API_KEY,
                          @Query("lang") lang: String = "ru"): Observable<ForecastList>


    companion object {
        fun create(): WeatherApi {
            val retrofit = Retrofit.Builder()
                .addConverterFactory(GsonConverterFactory.create())
                // instead of MoshiConvertFactory and call.enqueue
                .addCallAdapterFactory(RxJava2CallAdapterFactory.create())
                .baseUrl(BASE_URL)
                .build()
            return retrofit.create(WeatherApi::class.java)
        }
    }
}