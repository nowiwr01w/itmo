package com.example.sensetivecam

import java.io.File
import android.view.*
import kotlin.math.abs
import android.Manifest
import android.os.Bundle
import kotlinx.android.synthetic.main.activity_main.*
import android.content.pm.PackageManager
import android.util.Size
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import android.hardware.SensorEventListener
import androidx.camera.core.*
import java.io.FileOutputStream
import android.widget.ImageButton
import android.content.Context
import android.hardware.SensorEvent
import android.hardware.SensorManager
import android.hardware.Sensor
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import android.util.DisplayMetrics
import java.util.concurrent.Executors
import android.graphics.*
import android.util.Log
import java.util.*


private const val REQUEST_CODE_PERMISSIONS = 1

private val REQUIRED_PERMISSIONS = arrayOf(Manifest.permission.CAMERA)



class MainActivity : AppCompatActivity(), SensorEventListener {

    var accelerometerReading = FloatArray(3)
    var magnetometerReading = FloatArray(3)
    val orientationValues = FloatArray(3)

    var mSensorManager: SensorManager? = null

    private lateinit var viewFinder: TextureView

    private lateinit var OptionsFrag: TargetPath


    override fun onAccuracyChanged(sensor: Sensor?, accuracy: Int) {}
    override fun onSensorChanged(event: SensorEvent?) {
        if (event?.sensor?.type == Sensor.TYPE_ACCELEROMETER) {
                System.arraycopy(event.values, 0, accelerometerReading, 0, accelerometerReading.size)
        }
        else if (event?.sensor?.type == Sensor.TYPE_MAGNETIC_FIELD) {
                System.arraycopy(event.values, 0, magnetometerReading, 0, magnetometerReading.size)
        }

        val vArray = FloatArray(9)
        val check: Boolean = SensorManager.getRotationMatrix(vArray, null, accelerometerReading, magnetometerReading)
        if (check) {
            SensorManager.getOrientation(vArray, orientationValues)

        }
    }


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        mSensorManager = (getSystemService(Context.SENSOR_SERVICE) as SensorManager)
        viewFinder = findViewById(R.id.view_finder)
        val path = externalMediaDirs.first()
        OptionsFrag = TargetPath.create(path.toString())
        supportFragmentManager
            .beginTransaction()
            .add(frag.id, OptionsFrag)
            .hide(OptionsFrag)
            .commit()
        if (allPermissionsGranted()) {
            viewFinder.post {
                startCamera()
            }
        } else {
            ActivityCompat.requestPermissions(this, REQUIRED_PERMISSIONS, REQUEST_CODE_PERMISSIONS)
        }
    }


    override fun onResume() {
        mSensorManager!!.registerListener(this@MainActivity,
            (getSystemService(Context.SENSOR_SERVICE) as SensorManager).getDefaultSensor(Sensor.TYPE_ACCELEROMETER),
            SensorManager.SENSOR_DELAY_UI
        )
        mSensorManager!!.registerListener(
            this@MainActivity,
            (getSystemService(Context.SENSOR_SERVICE) as SensorManager).getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD),
            SensorManager.SENSOR_DELAY_UI
        )
        super.onResume()
    }


    override fun onPause() {
        super.onPause()
        mSensorManager!!.unregisterListener(this)
    }


    fun changeDir(view: View) {
        supportFragmentManager
            .beginTransaction()
            .show(OptionsFrag)
            .commit()
    }

    private val executor = Executors.newSingleThreadExecutor()


    override fun onRequestPermissionsResult(requestCode: Int, permissions: Array<String>, grantResults: IntArray) {
        if (requestCode == REQUEST_CODE_PERMISSIONS) {
            if (allPermissionsGranted()) {
                viewFinder.post {
                    startCamera()
                }
            } else {
                Toast.makeText(this, "Permissions not granted by the user.", Toast.LENGTH_SHORT).show()
                finish()
            }
        }
    }


    private fun allPermissionsGranted() = REQUIRED_PERMISSIONS.all {
        ContextCompat.checkSelfPermission(baseContext, it) == PackageManager.PERMISSION_GRANTED
    }


    private fun startCamera() {
        val previewConfig = PreviewConfig.Builder().apply {
            setTargetResolution(Size(DisplayMetrics().widthPixels, DisplayMetrics().heightPixels))
        }.build()

        val preview = Preview(previewConfig)
        preview.setOnPreviewOutputUpdateListener {
            val parent = viewFinder.parent as ViewGroup
            parent.removeView(viewFinder)
            parent.addView(viewFinder, 0)
            viewFinder.surfaceTexture = it.surfaceTexture
        }

        val imageCaptureConfig = ImageCaptureConfig.Builder()
            .apply {
                setCaptureMode(ImageCapture.CaptureMode.MIN_LATENCY)
                setFlashMode(FlashMode.AUTO)
            }.build()

        val imageCapture = ImageCapture(imageCaptureConfig)
        findViewById<ImageButton>(R.id.capture_button).setOnClickListener {
            Toast.makeText(baseContext, OptionsFrag.getData(), Toast.LENGTH_SHORT).show()
            val file = File(
                OptionsFrag.getData(),
                "${System.currentTimeMillis()}.jpg"
            )
            imageCapture.takePicture(file, executor,
                object : ImageCapture.OnImageSavedListener {
                    override fun onError(
                        imageCaptureError: ImageCapture.ImageCaptureError,
                        message: String,
                        exc: Throwable?
                    ) {
                        val msg = "Photo capture failed: $message  "
                        viewFinder.post {
                            Toast.makeText(baseContext, msg + OptionsFrag.getData(), Toast.LENGTH_SHORT).show()
                        }
                    }

                    override fun onImageSaved(file: File) {
                        val a = Math.toDegrees(orientationValues[1].toDouble())
                        val b = Math.toDegrees(orientationValues[2].toDouble())
                        val bm = BitmapFactory.decodeFile(file.absolutePath)
                        var bmm = bm.copy(Bitmap.Config.ARGB_8888, true)
                        var alpha = 0F
                        if (a in -90.0..-45.0) {
                            alpha = 90F
                        } else if (b < 0 && (abs(a) in 0.0..45.0) /*7 1*/) {
                            alpha = 0F
                        } else if (a in 45.0..90.0 /*1 3*/) {
                            alpha = -90F
                        } else if (b > 0 && (abs(a) in 0.0..45.0) /*3 9*/) {
                            alpha = 180F
                        }
                        bmm = bmm.rotate(alpha)

                        val can = Canvas(bmm)
                        val x: Float = (((can.height) / 3 * 2).toFloat())
                        val y: Float = ((can.width) / 3).toFloat()
                        val tf = Typeface.create("String!", Typeface.BOLD)
                        val paint = Paint()
                        paint.style = Paint.Style.FILL
                        paint.color = Color.CYAN
                        paint.typeface = tf
                        paint.textAlign = Paint.Align.CENTER
                        paint.textSize = 100F
                        can.drawText("$a", y, x, paint)
                        can.save()
                        val fOut = FileOutputStream(file.absoluteFile)
                        bmm.compress(Bitmap.CompressFormat.JPEG, 80, fOut)
                        fOut.close()
                    }
                })
        }
        CameraX.bindToLifecycle(this, preview, imageCapture)
    }


    fun Bitmap.rotate(degrees: Float): Bitmap {
        val matrix = Matrix().apply {
            postRotate(degrees)
        }
        return Bitmap.createBitmap(this, 0, 0, width, height, matrix, true)
    }

}
