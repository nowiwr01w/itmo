package com.example.sensetivecam

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import kotlinx.android.synthetic.main.fragment_target_path.*


class TargetPath : Fragment(), View.OnClickListener {

    var path = "something"

    fun getData(): String {
        return path
    }

    override fun onClick(v: View) {
        if (v.id == R.id.button) {
            path = edit_text.text.toString()
        }
        Toast.makeText(this.context, "onClick $path", Toast.LENGTH_SHORT).show()
        childFragmentManager
            .beginTransaction()
            .hide(this)
            .commit()
    }

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        return inflater.inflate(R.layout.fragment_target_path, container, false)
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        button.setOnClickListener(this)
        val args = arguments?.getString("str")
        path = args ?: ""
        edit_text.setText(path)
        Toast.makeText(this.context, "vCreated 2  $path", Toast.LENGTH_SHORT).show()
    }


    companion object {
        fun create(str : String): TargetPath {
            val frag = TargetPath()
            val arg = Bundle()
            arg.putString("str", str)
            frag.arguments = arg
            return frag
        }

    }
}
