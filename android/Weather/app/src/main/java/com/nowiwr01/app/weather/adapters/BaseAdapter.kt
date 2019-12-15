package com.nowiwr01.app.weather.adapters

import androidx.recyclerview.widget.RecyclerView

abstract class BaseAdapter<P>: RecyclerView.Adapter<BaseViewHolder<P>>() {

    protected var data: MutableList<P> = ArrayList()
    private var callback: BaseAdapterCallback<P>? = null

    var hasItems = false

    fun attachCallback(callback: BaseAdapterCallback<P>) {
        this.callback = callback
    }

    fun detachCallback() {
        this.callback = null
    }

    fun clearItems() {
        data.clear()
    }

    fun addItem(newItem: P) {
        data.add(newItem)
        notifyItemInserted(data.size - 1)
    }

    override fun onBindViewHolder(holder: BaseViewHolder<P>, position: Int) {
        holder.bind(data[position])

        holder.itemView.setOnClickListener {
            callback?.onItemClick(data[position], holder.itemView)
        }
    }

    override fun getItemCount() = data.count()
}