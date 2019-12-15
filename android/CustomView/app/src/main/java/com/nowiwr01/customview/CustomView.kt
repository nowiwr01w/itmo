package com.nowiwr01.customview

import android.animation.Animator
import android.animation.AnimatorListenerAdapter
import android.animation.AnimatorSet
import android.animation.ObjectAnimator
import android.annotation.SuppressLint
import android.content.Context
import android.content.res.TypedArray
import android.graphics.Canvas
import android.graphics.Paint
import android.graphics.RectF
import android.os.Parcel
import android.os.Parcelable
import android.util.AttributeSet
import android.util.TypedValue
import android.view.View
import android.view.animation.LinearInterpolator
import androidx.core.animation.doOnEnd
import kotlin.math.ceil
import kotlin.math.min

class CustomView @JvmOverloads constructor(
    context: Context, attrs: AttributeSet, defStyleAttr: Int = 0, defStyleRes: Int = 0
) : View(context, attrs, defStyleAttr, defStyleRes) {

    private val crossThick: Int
    private val crossLength: Int
    private val radius: Float
    private val distCrossAndLeftDot: Int
    private val distTopAndLeftDot: Int
    private val animationDelay: Int
    private val animationDuration: Int
    private var maxScale: Float
    private val loaderColor: Int

    private val crossPaint = Paint(Paint.ANTI_ALIAS_FLAG)
    private val verticalCrossRect: RectF
    private val horizontalCrossRect: RectF

    private val leftDot: RectF
    private val rightDot: RectF
    private val topDot: RectF
    private val downDot: RectF

    private val crossAnimator = ObjectAnimator.ofFloat(0f, 180f)

    private var topDotAnimatorTo: Animator
    private var topDotAnimatorFrom: Animator

    private var rightDotAnimatorTo: Animator
    private var rightDotAnimatorFrom: Animator

    private var downDotAnimatorTo: Animator
    private var downDotAnimatorFrom: Animator

    private var leftDotAnimatorTo: Animator
    private var leftDotAnimatorFrom: Animator

    private var animationUpdateRotation = 0f
        set(value) {
            field = value
            invalidate()
        }

    private var topDotScale = 1f
        set(value) {
            field = value
            invalidate()
        }

    private var rightDotScale = 1f
        set(value) {
            field = value
            invalidate()
        }

    private var downDotScale = 1f
        set(value) {
            field = value
            invalidate()
        }

    private var leftDotScale = 1f
        set(value) {
            field = value
            invalidate()
        }

    private var animator: AnimatorSet? = null

    init {
        isSaveEnabled = true
        val a: TypedArray =
            context.obtainStyledAttributes(attrs, R.styleable.CustomView, defStyleAttr, 0)
        try {
            loaderColor = a.getColor(R.styleable.CustomView_color, 0)
            maxScale = a.getFloat(R.styleable.CustomView_max_scale, 1.3f)
            animationDelay = a.getInt(R.styleable.CustomView_animation_latency, 1000)
            animationDuration = a.getInt(R.styleable.CustomView_animation_duration, 300)
            crossThick = a.getDimensionPixelSize(R.styleable.CustomView_cross_thick, dp(10f))
            crossLength = a.getDimensionPixelSize(R.styleable.CustomView_cross_length, dp(22f))
            radius = a.getDimensionPixelSize(R.styleable.CustomView_radius, dp(2.5f)).toFloat()
            distCrossAndLeftDot = a.getDimensionPixelSize(R.styleable.CustomView_destination_to_dot, dp(16f))
            distTopAndLeftDot = a.getDimensionPixelSize(R.styleable.CustomView_destination_between_dot, dp(6f))

            val crossFirstPart = (crossLength - crossThick).toFloat() / 2
            val crossSecondPart = (crossLength + crossThick).toFloat() / 2

            crossPaint.color = loaderColor

            // (left, top, right, bottom) - координаты
            // Подготавливаем крест, который представляет из себя 2 прямоугольника с закруглёнными краями
            verticalCrossRect = RectF(
                crossFirstPart,
                0f,
                crossSecondPart,
                crossLength.toFloat()
            )
            horizontalCrossRect = RectF(
                0f,
                crossFirstPart,
                crossLength.toFloat(),
                crossSecondPart
            )

            val fromCenterToDot = distTopAndLeftDot.toFloat() / 2
            val centerOfFourDot = crossLength + distCrossAndLeftDot + crossThick + distTopAndLeftDot.toFloat() / 2

            // Подготавливаем точки. Они так же являются прямоугольниками
            leftDot = RectF(
                (centerOfFourDot - fromCenterToDot - crossThick),
                crossFirstPart,
                (centerOfFourDot - fromCenterToDot),
                crossSecondPart
            )

            topDot = RectF(
                centerOfFourDot - crossThick / 2,
                0f,
                centerOfFourDot + crossThick / 2,
                crossThick.toFloat()
            )

            rightDot = RectF(
                centerOfFourDot + fromCenterToDot,
                crossFirstPart,
                centerOfFourDot + fromCenterToDot + crossThick,
                crossSecondPart
            )

            downDot = RectF(
                centerOfFourDot - crossThick / 2,
                (crossThick + distTopAndLeftDot).toFloat(),
                centerOfFourDot + crossThick / 2,
                (crossThick + distTopAndLeftDot + crossThick).toFloat()
            )

            // Штука, которая делает поворот креста на 180
            crossAnimator.apply {
                duration = animationDuration.toLong()
                addUpdateListener {
                    animationUpdateRotation = it.animatedValue as Float
                }
            }

            // Здесь идут парные: очки растягиваются и стягиваются
            topDotAnimatorTo = ObjectAnimator.ofFloat(1f, maxScale).apply {
                duration = animationDuration.toLong()
                addUpdateListener { topDotScale = animatedValue as Float }
            }

            topDotAnimatorFrom = ObjectAnimator.ofFloat(maxScale, 1f).apply {
                duration = animationDuration.toLong()
                addUpdateListener { topDotScale = animatedValue as Float }
            }

            rightDotAnimatorTo = ObjectAnimator.ofFloat(1f, maxScale).apply {
                duration = animationDuration.toLong()
                addUpdateListener { rightDotScale = animatedValue as Float }
            }

            rightDotAnimatorFrom = ObjectAnimator.ofFloat(maxScale, 1f).apply {
                duration = animationDuration.toLong()
                addUpdateListener { rightDotScale = animatedValue as Float }
            }

            downDotAnimatorTo = ObjectAnimator.ofFloat(1f, maxScale).apply {
                duration = animationDuration.toLong()
                addUpdateListener { downDotScale = animatedValue as Float }
            }

            downDotAnimatorFrom = ObjectAnimator.ofFloat(maxScale, 1f).apply {
                duration = animationDuration.toLong()
                addUpdateListener { downDotScale = animatedValue as Float }
            }

            leftDotAnimatorTo = ObjectAnimator.ofFloat(1f, maxScale).apply {
                duration = animationDuration.toLong()
                addUpdateListener { leftDotScale = animatedValue as Float }
            }
            leftDotAnimatorFrom = ObjectAnimator.ofFloat(maxScale, 1f).apply {
                duration = animationDuration.toLong()
                addUpdateListener { leftDotScale = animatedValue as Float }
            }

        } finally {
            a.recycle()
        }

    }

    override fun onMeasure(widthMeasureSpec: Int, heightMeasureSpec: Int) {
        setMeasuredDimension(
            getSize(
                widthMeasureSpec,
                crossLength + distCrossAndLeftDot + 2 * crossThick + distTopAndLeftDot + ceil(crossThick * (maxScale - 1)).toInt()
            ),
            getSize(heightMeasureSpec, crossLength + ceil(crossThick * maxScale).toInt() * 2)
        )
    }


    override fun onAttachedToWindow() {
        super.onAttachedToWindow()
        animator?.cancel()

        animator = AnimatorSet().apply {
            startDelay = animationDelay.toLong()
            interpolator = LinearInterpolator()
            // Сначала анимируем крестик, потом точки
            playSequentially(
                crossAnimator,
                topDotAnimatorTo,
                AnimatorSet().apply { playTogether(topDotAnimatorFrom, rightDotAnimatorTo) },
                AnimatorSet().apply { playTogether(rightDotAnimatorFrom, downDotAnimatorTo) },
                AnimatorSet().apply { playTogether(downDotAnimatorFrom, leftDotAnimatorTo) },
                leftDotAnimatorFrom
            )
            // Зацикливаем анимацию
            addListener(object : AnimatorListenerAdapter() {
                override fun onAnimationEnd(animation: Animator?) {
                    super.onAnimationEnd(animation)
                    startDelay = animationDelay.toLong()
                    start()
                }
            })
            start()
        }
    }

    override fun onDetachedFromWindow() {
        super.onDetachedFromWindow()
        animator?.cancel()
        animator = null
    }

    override fun onDraw(canvas: Canvas) {
        super.onDraw(canvas)

        // Так как квадрат
        val cx = crossLength.toFloat() / 2
        val cy = crossLength.toFloat() / 2

        // Координаты смещения
        val a = 0f
        val b = crossThick * maxScale

        // Смещаем нашу матрицу на a вправо и на b вниз
        canvas.translate(a, b)

        // Нужно запомнить состояние матрицы отрисовки, чтобы в конце она осталась такой же, как и в начале onDraw()
        val save = canvas.save()

        // Результат поворота: 0 -> 180 для каждой "точки"
        canvas.rotate(animationUpdateRotation, cx, cy)

        // Рисуем наш крест
        canvas.drawRoundRect(verticalCrossRect, radius, radius, crossPaint)
        canvas.drawRoundRect(horizontalCrossRect, radius, radius, crossPaint)

        // Возвращаем состояние матрицы в исходное
        canvas.restoreToCount(save)

        // Рисуем точки
        drawDot(leftDot, canvas, leftDotScale)
        drawDot(topDot, canvas, topDotScale)
        drawDot(rightDot, canvas, rightDotScale)
        drawDot(downDot, canvas, downDotScale)

    }


    private fun getSize(measureSpec: Int, desired: Int): Int {
        val mode = MeasureSpec.getMode(measureSpec)
        val size = MeasureSpec.getSize(measureSpec)
        return when (mode) {
            MeasureSpec.AT_MOST -> min(size, desired)
            MeasureSpec.EXACTLY -> size
            else -> desired
        }
    }

    private fun drawDot(rect: RectF, canvas: Canvas, scale: Float) {
        val save = canvas.save()
        // Растягивают на scale по х и у относительно сентра
        canvas.scale(scale, scale, rect.centerX(), rect.centerY())

        // Отрисовываем
        canvas.drawRoundRect(rect, radius, radius, crossPaint)

        // Возвращаем матрицу в исходное состояние
        canvas.restoreToCount(save)

    }

    private fun dp(dp: Float): Int {
        return (TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, dp, resources.displayMetrics)).toInt()
    }


    override fun onSaveInstanceState(): Parcelable? {
        val state = CustomViewState(super.onSaveInstanceState())
        animator?.pause()
        state.crossRotation = animationUpdateRotation
        state.topScale = topDotScale
        state.rightScale = rightDotScale
        state.downScale = downDotScale
        state.leftScale = leftDotScale
        state.animator = animator
        return state
    }

    override fun onRestoreInstanceState(state: Parcelable?) {
        if (state is CustomViewState) {
            animationUpdateRotation = state.crossRotation
            topDotScale = state.topScale
            rightDotScale = state.rightScale
            downDotScale = state.downScale
            leftDotScale = state.leftScale
            animator = state.animator
            animator?.resume()
        } else {
            super.onRestoreInstanceState(state)
        }
    }


    private class CustomViewState : BaseSavedState {

        var crossRotation = 0f
        var topScale = 1f
        var rightScale = 1f
        var downScale = 1f
        var leftScale = 1f
        var animator: AnimatorSet? = null

        constructor(superState: Parcelable?) : super(superState)

        constructor(parcel: Parcel) : super(parcel) {
            animator = parcel.readValue(null) as AnimatorSet
            crossRotation = parcel.readFloat()
            topScale = parcel.readFloat()
            rightScale = parcel.readFloat()
            downScale = parcel.readFloat()
            leftScale = parcel.readFloat()
        }

        override fun writeToParcel(out: Parcel, flags: Int) {
            super.writeToParcel(out, flags)

            // Порядок считывания и записи из парсела должен соответствовать друг другу
            out.writeValue(animator)
            out.writeFloat(crossRotation)
            out.writeFloat(topScale)
            out.writeFloat(rightScale)
            out.writeFloat(downScale)
            out.writeFloat(leftScale)
        }

        companion object {
            @JvmField
            val CREATOR = object : Parcelable.Creator<CustomViewState> {
                override fun createFromParcel(source: Parcel): CustomViewState = CustomViewState(source)
                override fun newArray(size: Int): Array<CustomViewState?> = arrayOfNulls(size)
            }
        }
    }

}
