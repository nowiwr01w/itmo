package com.nowiwr01.app.weather.adapters

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import kotlinx.android.synthetic.main.item_daily_forecast.view.*
import kotlinx.android.synthetic.main.item_daily_forecast.view.icon
import kotlinx.android.synthetic.main.item_daily_forecast.view.temperature
import com.nowiwr01.app.weather.R
import com.nowiwr01.app.weather.adapters.model.DailyForecast

class DailyForecastAdapter : BaseAdapter<DailyForecast>() {

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): DailyForecastViewHolder {
        return DailyForecastViewHolder(LayoutInflater
            .from(parent.context)
            .inflate(R.layout.item_daily_forecast, parent, false))
    }

    class DailyForecastViewHolder(itemView: View): BaseViewHolder<DailyForecast>(itemView) {

        override fun bind(model: DailyForecast) {
            itemView.icon.setImageResource(model.icon)
            itemView.date.text = model.date
            itemView.temperature.text = model.temperature
        }
    }
}