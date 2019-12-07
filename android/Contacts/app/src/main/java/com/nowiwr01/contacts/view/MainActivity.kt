package com.nowiwr01.contacts.view

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
import com.nowiwr01.contacts.adapters.ContactAdapter
import com.nowiwr01.contacts.model.Contact
import com.nowiwr01.contacts.utils.Utils
import kotlinx.android.synthetic.main.activity_main.*
import kotlinx.android.synthetic.main.not_found_layout.*
import kotlin.random.Random

class MainActivity : AppCompatActivity() {

    private val CODE_REQUEST = 1
    private lateinit var permissions: Array<String>
    private lateinit var contactList: ArrayList<Contact>
    private lateinit var contactAdapter: ContactAdapter

    private var myBroadCastReceiver: BroadcastReceiver? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        permissions = arrayOf(
            android.Manifest.permission.READ_CONTACTS,
            android.Manifest.permission.SEND_SMS
        )

        contactList = if (checkAndRequestPermission()) {
            getContacts()
        } else {
            arrayListOf()
        }

        if (contactList.isNotEmpty()) {
            showCount()
        }

        contactAdapter = ContactAdapter(contactList, applicationContext, {
            val intent = Intent(Intent.ACTION_DIAL, Uri.parse("tel:" + it.phoneNumber))
            startActivity(intent)
        }, {
            val intent = Intent(Intent.ACTION_SENDTO, Uri.parse("smsto:" + it.phoneNumber)).apply {
                putExtra("sms_body", "Вы тоже заметили, что Веда Воронина очень милая?")
            }
            startActivity(intent)
        })

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

    private fun checkAndRequestPermission(): Boolean {
        val permissionsNeeded: ArrayList<String> = arrayListOf()
        for (perm in permissions) {
            if (ContextCompat.checkSelfPermission(this, perm) != PackageManager.PERMISSION_GRANTED) {
                permissionsNeeded.add(perm)
            }
        }
        if (permissionsNeeded.isNotEmpty()) {
            ActivityCompat.requestPermissions(this, permissions, CODE_REQUEST)
            return false
        }
        return true
    }

    override fun onRequestPermissionsResult(requestCode: Int, permissions: Array<String>, grantResults: IntArray) {
        when (requestCode) {
            CODE_REQUEST -> {
                var denied = 0
                val deniedNames = arrayListOf<String>()
                for (i in grantResults.indices) {
                    if (grantResults[i] == PackageManager.PERMISSION_DENIED) {
                        deniedNames.add(permissions[i])
                        denied += 1
                    }
                }
                if (denied == 0) {
                    updateAndShowContactList()
                } else {
                    for (i in deniedNames.indices) {
                        checkDenyPermission(deniedNames, i)
                    }
                }
            }
        }
    }

    private fun updateAndShowContactList() {
        contactList = getContacts()
        contactAdapter.contactList = contactList
        contactAdapter.contactListFull = contactList
        contactAdapter.notifyDataSetChanged()
        showCount()
    }

    private fun checkDenyPermission(deniedNames: ArrayList<String>, index: Int) {
        // The first time when we click on "Deny"
        if (ActivityCompat.shouldShowRequestPermissionRationale(this, deniedNames[index])) {
            Snackbar.make(rootLayout, "Вам нужно дать все разрешения", Snackbar.LENGTH_LONG).setAction("Дать рарешение") {
                checkAndRequestPermission()
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

    companion object {
        const val CHANGE = 1703
        const val RESPONSE = "response"
        const val NOT_FOUND_TAG = "notFound"
    }
}