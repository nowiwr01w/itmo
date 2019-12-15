package com.nowiwr01.app.weather.adapters

import android.view.View

interface BaseAdapterCallback<T> {
    fun onItemClick(model: T, view: View)
}