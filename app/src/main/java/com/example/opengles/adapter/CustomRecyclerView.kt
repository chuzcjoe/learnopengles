package com.example.opengles.adapter

import android.graphics.Color
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.RadioButton
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.example.opengles.R


class CustomAdapter(private val mTitles: List<String>) :
    RecyclerView.Adapter<CustomAdapter.MyViewHolder>(), View.OnClickListener {

    private lateinit var mOnItemClickListener: OnItemClickListener

    private var mSelectIndex: Int = 0

    class MyViewHolder(view: View) : RecyclerView.ViewHolder(view) {

        var mRadioButton: RadioButton
        var mTitle: TextView

        init {
            mRadioButton = view.findViewById(R.id.radio_btn)
            mTitle = view.findViewById(R.id.item_title)
        }
    }

    override fun onCreateViewHolder(viewGroup: ViewGroup, viewType: Int): MyViewHolder {
        val view = LayoutInflater.from(viewGroup.context)
            .inflate(R.layout.single_row, viewGroup, false)
        view.setOnClickListener(this)
        return MyViewHolder(view)
    }

    override fun onClick(view: View?) {
        if (mOnItemClickListener != null) {
            mOnItemClickListener.onItemClick(view, view!!.tag as Int)
        }
    }

    // Replace the contents of a view (invoked by the layout manager)
    override fun onBindViewHolder(holder: MyViewHolder, position: Int) {
        // Get element from your dataset at this position and replace the
        // contents of the view with that element
        holder.mTitle.text = mTitles[position]
        if (position == mSelectIndex) {
            holder.mRadioButton.isChecked = true
            holder.mTitle.setTextColor(Color.RED)
        } else {
            holder.mRadioButton.isChecked = false
            holder.mTitle.text = mTitles[position]
            holder.mTitle.setTextColor(Color.GRAY)
        }
        holder.itemView.tag = position
    }

    // Return the size of your dataset (invoked by the layout manager)
    override fun getItemCount() = mTitles.size

    fun addOnItemClickListener(listener: OnItemClickListener) {
        mOnItemClickListener = listener
    }

    interface OnItemClickListener {
        fun onItemClick(view: View?, position: Int)
    }

    fun setIndex(index: Int) {
        mSelectIndex = index
    }

    fun getIndex() : Int {
        return mSelectIndex
    }
}

