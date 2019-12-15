package com.nowiwr01.app.weather.presenters

import io.reactivex.disposables.CompositeDisposable
import io.reactivex.disposables.Disposable

abstract class BasePresenter<V: WeatherContract.BaseContract> {

    protected lateinit var view: V

    private val compositeDisposable = CompositeDisposable()

    fun subscribe(disposable: Disposable) {
        compositeDisposable.add(disposable)
    }

    fun attach(view: V) {
        this.view = view
    }

    fun detach() {
        compositeDisposable.clear()
    }
}