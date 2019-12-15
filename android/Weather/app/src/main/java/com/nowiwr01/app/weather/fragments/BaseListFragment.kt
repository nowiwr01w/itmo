package com.nowiwr01.app.weather.fragments

import android.os.Bundle
import android.view.View
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import kotlinx.android.synthetic.main.fragment_hourly_forecast.*
import com.nowiwr01.app.weather.adapters.BaseAdapter

abstract class BaseListFragment<M> : BaseFragment() {

    private lateinit var recyclerView: RecyclerView
    protected lateinit var viewAdapter: BaseAdapter<M>

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        viewAdapter = createAdapterInstance()
        recyclerView = list.apply {
            setHasFixedSize(true)
            layoutManager = LinearLayoutManager(context)
            adapter = viewAdapter
        }
    }

    override fun onRefresh() {
        swipeRefresh.isRefreshing = false
    }

    abstract fun createAdapterInstance(): BaseAdapter<M>

}