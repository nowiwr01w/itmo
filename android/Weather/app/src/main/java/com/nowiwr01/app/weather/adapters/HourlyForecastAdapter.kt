package com.nowiwr01.app.weather.adapters

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import kotlinx.android.synthetic.main.item_hourly_forecast.view.*
import kotlinx.android.synthetic.main.item_hourly_forecast.view.datetime
import kotlinx.android.synthetic.main.item_hourly_forecast.view.description
import kotlinx.android.synthetic.main.item_hourly_forecast.view.icon
import com.nowiwr01.app.weather.R
import com.nowiwr01.app.weather.adapters.model.HourlyForecast

class HourlyForecastAdapter: BaseAdapter<HourlyForecast>() {

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): HourlyForecastViewHolder {
        return HourlyForecastViewHolder(LayoutInflater
                .from(parent.context)
                .inflate(R.layout.item_hourly_forecast, parent, false))
    }

    class HourlyForecastViewHolder(itemView: View): BaseViewHolder<HourlyForecast>(itemView) {

        override fun bind(model: HourlyForecast) {
            itemView.icon.setImageResource(model.icon)
            itemView.datetime.text = model.datetime
            itemView.lowTemp.text = model.lowTemp
            itemView.highTemp.text = model.highTemp
            itemView.description.text = model.description
        }
    }
}