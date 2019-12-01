package com.example.networking.services

import android.app.IntentService
import android.content.Intent
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import androidx.localbroadcastmanager.content.LocalBroadcastManager
import com.example.networking.view.MoviesActivity.Companion.PICTURE_TAG
import java.io.ByteArrayOutputStream
import java.net.URL

class MoviesService : IntentService("MoviesService") {

    init {
        setIntentRedelivery(true)
    }

    override fun onHandleIntent(intent: Intent?) {

        val url = intent?.getStringExtra(PICTURE_TAG) ?: return
        val image = BitmapFactory.decodeStream(URL(url).openConnection().getInputStream())

        LocalBroadcastManager.getInstance(baseContext).sendBroadcast(Intent().apply {
            action = RESPONSE_TAG
            addCategory(Intent.CATEGORY_DEFAULT)
            putExtra(BYTE_ARRAY_TAG, ByteArrayOutputStream().apply {
                    image.compress(Bitmap.CompressFormat.JPEG, 100, this)
                }.toByteArray()
            )
        })
    }

    companion object {
        const val RESPONSE_TAG = "response"
        const val BYTE_ARRAY_TAG = "byteArray"
    }
}