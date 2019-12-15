package com.nowiwr01.app.weather.presenters

import io.reactivex.Observable
import io.reactivex.android.schedulers.AndroidSchedulers
import io.reactivex.schedulers.Schedulers
import com.nowiwr01.app.weather.utils.ApiUtils
import com.nowiwr01.app.weather.utils.Utils
import com.nowiwr01.app.weather.fragments.HomeFragment
import com.nowiwr01.app.weather.rest.model.current.CurrentWeatherModel
import com.nowiwr01.app.weather.rest.model.forecast.ForecastWeatherModel

class HomePresenter : BasePresenter<HomeFragment>() {

    @ExperimentalStdlibApi
    fun loadWeatherByCity(city: String) {
        val midDayRange: IntRange = 12..14
        view.showProgress()

        val currentWeatherObservable = ApiUtils.weatherApi.getWeatherByCity(city)

        val forecastWeatherObservable = ApiUtils.weatherApi.getForecastByCity(city)
            .flatMap { forecastList ->
                Observable.fromIterable(forecastList.forecast).filter {
                    val hours = Utils.getHours(it.dt + forecastList.city.timezone)
                    hours in midDayRange
                }
            }

        subscribe(Observable.concat(currentWeatherObservable, forecastWeatherObservable)
            .subscribeOn(Schedulers.io())
            .observeOn(AndroidSchedulers.mainThread())
            .doOnComplete { view.hideProgress() }
            .subscribe(
                { model ->
                when (model) {
                    is CurrentWeatherModel -> {
                        view.updateWeather(model)
                    }
                    is ForecastWeatherModel -> {
                        view.addDay(model)
                    }
                }
            }, {
                view.showError()
            })
        )
    }
}