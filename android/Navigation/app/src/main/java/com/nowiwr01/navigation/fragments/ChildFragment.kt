package com.nowiwr01.navigation.fragments

import android.os.Bundle
import android.transition.Slide
import android.view.Gravity
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.fragment.app.Fragment
import com.nowiwr01.navigation.MainActivity.Companion.TAG_CHAPTER
import com.nowiwr01.navigation.MainActivity.Companion.TAG_PROFILE
import com.nowiwr01.navigation.MainActivity.Companion.TAG_STORE
import com.nowiwr01.navigation.R
import kotlinx.android.synthetic.main.child_fragment.*

class ChildFragment : Fragment() {

    private lateinit var count: String

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        count = arguments?.getString(KEY_COUNT) ?: ""
    }

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        return inflater.inflate(R.layout.child_fragment, container, false)
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        val text = "$tag: $count"
        text_count.text = text

        button_next.setOnClickListener {
            val newFragment = newInstance(fragmentManager!!.backStackEntryCount.toString())

            val gravity = when (tag) {
                TAG_PROFILE -> Gravity.START
                TAG_CHAPTER -> Gravity.TOP
                TAG_STORE -> Gravity.END
                else -> Gravity.BOTTOM
            }

            newFragment.apply {
                enterTransition = Slide(gravity).apply {
                    duration = 600
                }
                exitTransition = Slide(Gravity.BOTTOM).apply {
                    duration = 300
                }
            }

            fragmentManager!!
                .beginTransaction()
                .add(R.id.child_container, newFragment, tag)
                .hide(this)
                .addToBackStack(tag)
                .commit()
        }
    }

    companion object {
        private const val KEY_COUNT = "count"

        fun newInstance(count: String?): ChildFragment {
            return ChildFragment().apply {
                arguments = Bundle().apply {
                    putString(KEY_COUNT, count)
                }
            }
        }
    }
}