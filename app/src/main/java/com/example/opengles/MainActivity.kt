package com.example.opengles

import android.content.res.ColorStateList
import android.graphics.Color
import android.opengl.GLSurfaceView
import android.os.Bundle
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

    companion object {
        val GLOptionList = listOf<String>(
            "Draw A Triangle",
        )
    }
}