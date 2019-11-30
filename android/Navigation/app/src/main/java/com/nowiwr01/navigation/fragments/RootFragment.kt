package com.nowiwr01.navigation.fragments

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.fragment.app.Fragment
import com.nowiwr01.navigation.R

class RootFragment : Fragment() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        retainInstance = true
    }

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        return inflater.inflate(R.layout.root_fragment, container, false)
    }

    fun addFirstChild() {
        val firstChild = ChildFragment.newInstance("0")
        childFragmentManager
            .beginTransaction()
            .add(R.id.child_container, firstChild, tag)
            .addToBackStack(tag)
            .commit()
    }
}