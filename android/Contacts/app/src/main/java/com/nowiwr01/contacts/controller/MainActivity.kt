package com.nowiwr01.contacts.controller

import com.google.android.material.snackbar.Snackbar
import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.content.IntentFilter
import android.content.pm.PackageManager
import android.net.Uri
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.provider.ContactsContract
import android.provider.Settings
import android.view.Menu
import android.view.MenuItem
import android.view.View
import androidx.appcompat.widget.SearchView
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import androidx.localbroadcastmanager.content.LocalBroadcastManager
import androidx.recyclerview.widget.LinearLayoutManager
import com.nowiwr01.contacts.R
import com.nowiwr01.contacts.adapters.CHANGE
import com.nowiwr01.contacts.adapters.ContactAdapter
import com.nowiwr01.contacts.adapters.RESPONSE
import com.nowiwr01.contacts.model.Contact
import com.nowiwr01.contacts.utils.Utils
import kotlinx.android.synthetic.main.activity_main.*
import kotlinx.android.synthetic.main.not_found_layout.*
import kotlin.random.Random

const val NOT_FOUND_TAG = "notFound"

class MainActivity : AppCompatActivity() {

    private val CODE_REQUEST = 1
    private lateinit var contactList: ArrayList<Contact>
    private lateinit var contactAdapter: ContactAdapter

    private var myBroadCastReceiver: BroadcastReceiver? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        if (ContextCompat.checkSelfPermission(this,
                android.Manifest.permission.READ_CONTACTS) != PackageManager.PERMISSION_GRANTED) {
            contactList = arrayListOf()
            ActivityCompat.requestPermissions(this,
                arrayOf(android.Manifest.permission.READ_CONTACTS), CODE_REQUEST)
        } else {
            contactList = getContacts()
        }

        if (contactList.isNotEmpty()) {
            showCount()
        }

        contactAdapter = ContactAdapter(contactList, applicationContext) {
            val intent = Intent(Intent.ACTION_DIAL, Uri.parse("tel:" + it.phoneNumber))
            startActivity(intent)
        }

        toolbar.apply {
            title = "Contacts"
            setSupportActionBar(toolbar)
        }

        contactRecyclerView.apply {
            setHasFixedSize(true)
            adapter = contactAdapter
            layoutManager = LinearLayoutManager(applicationContext)
        }

        myBroadCastReceiver = object : BroadcastReceiver() {
            override fun onReceive(context: Context?, intent: Intent?) {
                val change = intent?.getIntExtra(NOT_FOUND_TAG, 0)
                if (change == CHANGE) {
                    setNotFoundScreen()
                } else {
                    offNotFoundScreen()
                }
            }
        }

        LocalBroadcastManager.getInstance(this).registerReceiver(myBroadCastReceiver as BroadcastReceiver,
            IntentFilter(RESPONSE).apply {
                addCategory(Intent.CATEGORY_DEFAULT)
            })
    }

    private fun setNotFoundScreen() {
        tvNotFound.visibility = View.VISIBLE
        imgNotFound.visibility = View.VISIBLE
    }

    private fun offNotFoundScreen() {
        tvNotFound.visibility = View.GONE
        imgNotFound.visibility = View.GONE
    }

    private fun getContacts(): ArrayList<Contact> {
        contentResolver.query(
            ContactsContract.CommonDataKinds.Phone.CONTENT_URI, null,
            null, null, null).use { cursor ->
            if (cursor == null) {
                return arrayListOf()
            }
            val resultContacts = ArrayList<Contact>()
            while (cursor.moveToNext()) {
                val name = cursor.getString(cursor.getColumnIndex(ContactsContract.CommonDataKinds.Phone.DISPLAY_NAME)) ?: "N/A"
                val phoneNumber = cursor.getString(cursor.getColumnIndex(ContactsContract.CommonDataKinds.Phone.NUMBER)) ?: "N/A"
                val profileIcon = Utils.images[Random.nextInt(Utils.images.size)]
                resultContacts.add(Contact(name, phoneNumber, profileIcon))
            }
            return resultContacts
        }
    }

    private fun showCount() {
        val listSize = contactList.size
        val itemsFound = resources.getQuantityString(R.plurals.numberOfItems, listSize, listSize)
        Snackbar.make(rootLayout, itemsFound, Snackbar.LENGTH_LONG).show()
    }

    override fun onRequestPermissionsResult(requestCode: Int, permissions: Array<String>, grantResults: IntArray) {
        when (requestCode) {
            CODE_REQUEST -> {
                if (grantResults.isNotEmpty() && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    contactList = getContacts()
                    contactAdapter.contactList = contactList
                    contactAdapter.contactListFull = contactList
                    contactAdapter.notifyDataSetChanged()
                    showCount()
                } else {
                    checkDenyPermission(permissions)
                }
                return
            }
        }
    }

    private fun checkDenyPermission(permissions: Array<String>) {
        // The first time when we click on "Deny"
        if (ActivityCompat.shouldShowRequestPermissionRationale(this, permissions[0])) {
            Snackbar.make(rootLayout, "Разрешение отклонено", Snackbar.LENGTH_LONG).setAction("Дать рарешение") {
                ActivityCompat.requestPermissions(this,
                    arrayOf(android.Manifest.permission.READ_CONTACTS), CODE_REQUEST)
            }.show()
        } else {
            // "Never ask again" is checked
            Snackbar.make(rootLayout, "Нужно перейти в настройки", Snackbar.LENGTH_LONG).setAction("Перейти") {
                val intent = Intent(
                    Settings.ACTION_APPLICATION_DETAILS_SETTINGS,
                    Uri.fromParts("package", packageName, null))
                intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK)
                startActivity(intent)
                finish()
            }.show()
        }
    }

    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        menuInflater.inflate(R.menu.menu, menu)
        return super.onCreateOptionsMenu(menu)
    }

    override fun onOptionsItemSelected(item: MenuItem?): Boolean {
        if (item!!.itemId == R.id.search) {
            val searchView = item.actionView as SearchView
            searchView.queryHint = "Type here to Search"
            searchView.setOnQueryTextListener(object : SearchView.OnQueryTextListener {
                override fun onQueryTextSubmit(curRequest: String?): Boolean {
                    item.collapseActionView()
                    return false
                }
                override fun onQueryTextChange(prefix: String?): Boolean {
                    contactAdapter.filter.filter(prefix)
                    return false
                }
            })
        }
        return true
    }
}
