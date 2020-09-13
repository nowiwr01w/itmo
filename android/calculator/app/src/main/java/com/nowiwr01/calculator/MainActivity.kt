package com.nowiwr01.calculator

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.text.method.ScrollingMovementMethod
import android.view.View
import android.widget.ScrollView
import android.widget.Toast
import com.udojava.evalex.Expression
import kotlinx.android.synthetic.main.activity_main.*
import java.math.BigDecimal

class MainActivity : AppCompatActivity() {

    private val map = listOf(
        R.id.btn0 to "0", R.id.btn1 to "1", R.id.btn2 to "2", R.id.btn3 to "3", R.id.btn4 to "4",
        R.id.btn5 to "5", R.id.btn6 to "6", R.id.btn7 to "7", R.id.btn8 to "8", R.id.btn9 to "9",
        R.id.btnPlus to "+", R.id.btnMinus to "-", R.id.btnMultiply to "*", R.id.btnDivide to "/",
        R.id.btnDot to "."
    )

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        map.forEach { pair ->
            findViewById<View>(pair.first).setOnClickListener {
                tvResult.text = String.format("%s%s", tvResult.text, pair.second)
                scrollTo(false)
            }
        }
        btnDelete.setOnClickListener {
            tvResult.text = tvResult.text.dropLast(1)
        }
        btnDelete.setOnLongClickListener {
            tvResult.text = ""
            true
        }
        btnEq.setOnClickListener {
            try {
                val result = Expression(tvResult.text.toString()).eval()
                tvResult.text = String.format("%s", result)
                scrollTo(true)
            } catch (throwable: Throwable) {
                Toast.makeText(applicationContext, throwable.localizedMessage, Toast.LENGTH_LONG).show()
            }
        }
    }

    private fun scrollTo(start: Boolean) {
        val method = if (start) View.FOCUS_LEFT else View.FOCUS_RIGHT
        scrollable.post {
            scrollable.fullScroll(method)
        }
    }

    override fun onSaveInstanceState(outState: Bundle) {
        outState.putString(EXPRESSION, tvResult.text.toString())
        super.onSaveInstanceState(outState)
    }

    override fun onRestoreInstanceState(savedInstanceState: Bundle) {
        super.onRestoreInstanceState(savedInstanceState)
        tvResult.text = savedInstanceState.getString(EXPRESSION, "")
    }

    companion object {
        const val EXPRESSION = "EXPRESSION"
    }
}