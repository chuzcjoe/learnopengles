package com.example.opengles

import android.content.res.ColorStateList
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.graphics.Color
import android.opengl.GLSurfaceView
import android.opengl.GLSurfaceView.RENDERMODE_CONTINUOUSLY
import android.os.Bundle
import android.util.Log
import android.view.LayoutInflater
import android.view.Menu
import android.view.MenuItem
import android.view.View
import android.view.ViewGroup
import android.view.ViewTreeObserver.OnGlobalLayoutListener
import android.widget.Button
import android.widget.RelativeLayout
import androidx.appcompat.app.AlertDialog
import androidx.appcompat.app.AppCompatActivity
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.opengles.adapter.CustomAdapter
import com.example.opengles.gl.MyGLRender
import com.example.opengles.gl.MyGLSurfaceView
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch
import java.nio.ByteBuffer

class MainActivity : AppCompatActivity(), OnGlobalLayoutListener {
    // Variables
    private var mIndex: Int = 0;
    private lateinit var mGLSurfaceView: GLSurfaceView
    private lateinit var mRootView: ViewGroup
    private val mGLRender = MyGLRender()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        mRootView = findViewById<View>(R.id.rootView) as ViewGroup
        mRootView.viewTreeObserver.addOnGlobalLayoutListener(this)
        mGLRender.initRenderContext()
    }

    override fun onGlobalLayout() {
        mRootView.viewTreeObserver.removeOnGlobalLayoutListener(this)
        val lp = RelativeLayout.LayoutParams(
            ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT
        )
        lp.addRule(RelativeLayout.CENTER_IN_PARENT)
        mGLSurfaceView = MyGLSurfaceView(this, mGLRender, null)
        mRootView.addView(mGLSurfaceView, lp)
        mGLSurfaceView.renderMode = GLSurfaceView.RENDERMODE_CONTINUOUSLY
    }

    override fun onCreateOptionsMenu(menu: Menu): Boolean {
        menuInflater.inflate(R.menu.menu_main, menu)
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        val id = item.itemId
        if (id == R.id.action_change_sample) {
            showGLOptions();
        }
        return true;
    }

    private fun showGLOptions() {
        val builder = AlertDialog.Builder(this)
        val inflater = LayoutInflater.from(this)
        val rootView = inflater.inflate(R.layout.text_row_item, null)
        val dialog = builder.create()

        // Ok button
        val okBtn = rootView.findViewById<Button>(R.id.confirm_btn)
        val originalColor = okBtn.backgroundTintList
        okBtn.setOnClickListener {
            // Set the button color to gray
            it.backgroundTintList = ColorStateList.valueOf(Color.GREEN)

            // Use a coroutine to delay for 100ms and then revert the color
            CoroutineScope(Dispatchers.Main).launch {
                delay(100L)
                it.backgroundTintList = originalColor
                dialog.cancel()
            }
        }

        val myViewAdapter = CustomAdapter(GLOptionList)
        var resolutionsListView = rootView.findViewById<RecyclerView>(R.id.resolution_list_view)
        myViewAdapter.setIndex(mIndex)
        myViewAdapter.addOnItemClickListener(object: CustomAdapter.OnItemClickListener{
            override fun onItemClick(view: View?, position: Int) {
                mRootView.removeView(mGLSurfaceView)
                val lp = RelativeLayout.LayoutParams(
                    ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT
                )
                lp.addRule(RelativeLayout.CENTER_IN_PARENT)
                mGLSurfaceView = MyGLSurfaceView(this@MainActivity, mGLRender)
                mRootView.addView(mGLSurfaceView, lp)

                val selectIndex = myViewAdapter.getIndex()
                myViewAdapter.setIndex(position)
                myViewAdapter.notifyItemChanged(selectIndex)
                myViewAdapter.notifyItemChanged(position)
                mIndex = position
                mGLSurfaceView.renderMode = GLSurfaceView.RENDERMODE_WHEN_DIRTY

                if (mRootView.width != mGLSurfaceView.width || mRootView.height != mGLSurfaceView.height) {
                    (mGLSurfaceView as MyGLSurfaceView).setAspectRatio(mRootView.width, mRootView.height)
                }

                mGLRender.setSample(position)

                when (position) {
                    SAMPLE_TRIANGLE -> {
                        Log.d(TAG, "Draw a triangle")
                    }
                    SAMPLE_LOAD_TEXTURE -> {
                        loadBitmap(R.drawable.monkey)
                    }
                    SAMPLE_VAO_VBO -> {
                        Log.d(TAG, "VAO and VBO sample")
                    }
                    SAMPLE_FBO -> {
                        loadBitmap(R.drawable.monkey)
                        Log.d(TAG, "FBO sample")
                    }
                    SAMPLE_TRANSFORMATION -> {
                        // continuously draw to show transformation animation
                        mGLSurfaceView.renderMode = RENDERMODE_CONTINUOUSLY
                        loadBitmap(R.drawable.monkey)
                        Log.d(TAG, "Transformation sample")
                    }
                }

                mGLSurfaceView.requestRender()
                dialog.cancel()
            }

        })

        val manager = LinearLayoutManager(this)
        manager.orientation = LinearLayoutManager.VERTICAL
        resolutionsListView.layoutManager = manager

        resolutionsListView.adapter = myViewAdapter
        resolutionsListView.scrollToPosition(mIndex)

        dialog.show()
        dialog.window?.setContentView(rootView)
    }

    private fun loadBitmap(resId: Int): Bitmap? {
        val fileStream = this.resources.openRawResource(resId)
        val bitmap: Bitmap? = BitmapFactory.decodeStream(fileStream)
        if (bitmap != null) {
            val buf = ByteBuffer.allocate(bitmap.byteCount)
            bitmap.copyPixelsToBuffer(buf)
            val byteArray = buf.array()
            mGLRender.setImageData(IMAGE_FORMAT_RGBA, bitmap.width, bitmap.height, byteArray)
            Log.d(TAG, "image width: ${bitmap.width}, image height: ${bitmap.height}")
        }
        return bitmap
    }

    companion object {
        val TAG: String = "OPENGLES"
        val GLOptionList = listOf<String>(
            "Draw A Triangle",
            "Load Texture",
            "VAO and VBO",
            "FBO",
            "Transformation"
        )

        const val IMAGE_FORMAT_RGBA = 0x00

        const val SAMPLE_TRIANGLE = 0x00
        const val SAMPLE_LOAD_TEXTURE = 0x01
        const val SAMPLE_VAO_VBO = 0x02
        const val SAMPLE_FBO = 0x03;
        const val SAMPLE_TRANSFORMATION = 0x04;
    }
}