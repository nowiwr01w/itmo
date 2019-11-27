package com.nowiwr01.contacts.adapters

import android.content.Context
import android.content.Intent
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Filter
import android.widget.Filterable
import android.widget.ImageView
import android.widget.TextView
import androidx.localbroadcastmanager.content.LocalBroadcastManager
import androidx.recyclerview.widget.RecyclerView
import com.nowiwr01.contacts.R
import com.nowiwr01.contacts.model.Contact
import kotlinx.android.synthetic.main.contact_item.view.*
import java.util.*
import kotlin.collections.ArrayList

const val CHANGE = 1703
const val RESPONSE = "response"
const val NOT_FOUND_TAG = "notFound"

class ContactAdapter(
    var contactList: ArrayList<Contact>,
    private val context: Context,
    private val onClick: (Contact) -> Unit
) : RecyclerView.Adapter<ContactAdapter.ContactViewHolder>(), Filterable {

    private var isChange = 0
    var contactListFull: ArrayList<Contact> = ArrayList(contactList)

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ContactViewHolder {
        val holder = ContactViewHolder(LayoutInflater.from(context).inflate(R.layout.contact_item, parent, false))
        holder.itemView.setOnClickListener {
            onClick(contactList[holder.adapterPosition])
        }
        return holder
    }

    override fun onBindViewHolder(holder: ContactViewHolder, position: Int) {
        holder.bind(contactList[position], context)
    }

    override fun getItemCount() = contactList.size

    inner class ContactViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {

        private val name: TextView = itemView.profile_name
        private val phone: TextView = itemView.profile_prone_number
        private var profileIcon: ImageView = itemView.profile_image

        fun bind(contactItem: Contact, context: Context) {
            name.text = contactItem.name
            phone.text = contactItem.phoneNumber

            val resourceID = context.resources.getIdentifier(contactItem.profileIcon, "drawable", context.packageName)
            profileIcon.setImageResource(resourceID)
        }
    }

    class SearchFilter(
        private val contactListFull:List<Contact>,
        private val listener: (List<Contact>) -> Unit
    ) : Filter() {

        fun filterResults(constraint: CharSequence?): ArrayList<Contact> {
            val searchList = arrayListOf<Contact>()
            if (constraint == null || constraint.isEmpty()) {
                searchList.addAll(contactListFull)
            } else {
                val filterPattern = constraint.toString().toLowerCase(Locale.getDefault()).trim()
                for (contact: Contact in contactListFull) {
                    if (contact.name.toLowerCase(Locale.getDefault()).contains(filterPattern) ||
                        contact.phoneNumber.contains(filterPattern)) {
                        searchList.add(contact)
                    }
                }
            }
            return searchList
        }

        override fun performFiltering(charSequence: CharSequence?): FilterResults {
            val results = FilterResults()
            results.values = filterResults(charSequence)
            return results
        }

        override fun publishResults(p0: CharSequence?, results: FilterResults?) {
            listener(results?.values as List<Contact>)
        }
    }

    override fun getFilter(): SearchFilter {
        return SearchFilter(contactListFull) { resultList ->
            contactList.clear()
            contactList.addAll(resultList)
            notifyDataSetChanged()
            isChange = if (contactList.isEmpty()) {
                CHANGE
            } else {
                0
            }
            showNotFoundPage(isChange)
        }
    }

    private fun showNotFoundPage(isChange: Int) {
        LocalBroadcastManager.getInstance(context).sendBroadcast(Intent().apply {
            action = RESPONSE
            addCategory(Intent.CATEGORY_DEFAULT)
            putExtra(NOT_FOUND_TAG, isChange)
        })
    }
}