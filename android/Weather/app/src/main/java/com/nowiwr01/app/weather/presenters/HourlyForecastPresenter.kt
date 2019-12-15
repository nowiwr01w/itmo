package com.nowiwr01.app.weather.presenters

import io.reactivex.Observable
import io.reactivex.android.schedulers.AndroidSchedulers
import io.reactivex.schedulers.Schedulers
import com.nowiwr01.app.weather.utils.ApiUtils
import com.nowiwr01.app.weather.utils.Utils
import com.nowiwr01.app.weather.fragments.HourlyForecastFragment

class HourlyForecastPresenter : BasePresenter<HourlyForecastFragment>() {

    @ExperimentalStdlibApi
    fun loadForecastForDayByCity(day: String, city: String) {

        view.showProgress()

        subscribe(ApiUtils.weatherApi.getForecastByCity(city)
            .subscribeOn(Schedulers.io())
            .observeOn(AndroidSchedulers.mainThread())
            .doOnNext {
                view.setTimezone(it.city.timezone)
            }
            .flatMap { forecastList ->
                Observable.fromIterable(forecastList.forecast).filter {
                    day.startsWith(Utils.getDateTime(it.dt + forecastList.city.timezone, "dd"))
                }
            }
            .doOnComplete { view.hideProgress() }
            .subscribe({
                view.addHour(it)
            }, {
                view.showError()
            })
        )

    }
}