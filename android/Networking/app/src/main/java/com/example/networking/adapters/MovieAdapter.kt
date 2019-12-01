package com.example.networking.adapters

import android.content.Context
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.example.networking.R
import com.example.networking.model.Movie
import com.squareup.picasso.Picasso
import kotlinx.android.synthetic.main.movie_item.view.*
import kotlin.collections.ArrayList

class MovieAdapter(
    var movieList: ArrayList<Movie>,
    private val context: Context,
    private val onClick: (Movie) -> Unit
) : RecyclerView.Adapter<MovieAdapter.MyViewHolder>() {

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): MyViewHolder {
        val holder = MyViewHolder(LayoutInflater.from(context).inflate(R.layout.movie_item, parent, false))
        holder.itemView.setOnClickListener {
            onClick(movieList[holder.adapterPosition])
        }
        return holder
    }
    override fun onBindViewHolder(holder: MyViewHolder, position: Int) {
        holder.bind(movieList[position])
    }

    override fun getItemCount() = movieList.size

    class MyViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {

        private val picture: ImageView = itemView.picture
        private val title: TextView = itemView.title
        private val year: TextView = itemView.year

        fun bind(movie: Movie) {
            title.text = movie.title
            year.text = movie.year
            Picasso.get().load(movie.picture).fit().centerInside().into(picture)
        }
    }
}