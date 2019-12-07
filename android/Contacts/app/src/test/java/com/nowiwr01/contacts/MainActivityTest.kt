package com.nowiwr01.contacts

import android.app.Activity
import androidx.appcompat.widget.SearchView
import androidx.appcompat.widget.Toolbar
import androidx.recyclerview.widget.RecyclerView
import com.nowiwr01.contacts.view.MainActivity
import org.junit.Assert
import org.junit.Before
import org.junit.Test
import org.junit.runner.RunWith
import org.robolectric.Robolectric
import org.robolectric.RobolectricTestRunner
import org.robolectric.Shadows

@RunWith(RobolectricTestRunner::class)
class MainActivityTest {

    private lateinit var activity: Activity
    private lateinit var activity1: Activity

    @Before
    fun setup() {
        activity = Robolectric.buildActivity(MainActivity::class.java).create().get()
        activity1 = Robolectric.buildActivity(MainActivity::class.java).create().visible().get()
    }

    @Test
    fun toolbarNotNullTest() {
        val toolbar: Toolbar = activity.findViewById(R.id.toolbar)
        Assert.assertNotNull("Toolbar is null", toolbar)
    }

    @Test
    fun recyclerNotNullTest() {
        val recyclerView: RecyclerView = activity.findViewById(R.id.contactRecyclerView)
        Assert.assertNotNull("ContactsRecyclerView is null", recyclerView)
    }

    @Test
    fun menuAndSearchViewNotNullTest() {
        val searchItem = Shadows.shadowOf(activity1).optionsMenu.findItem(R.id.search)
        Assert.assertTrue(searchItem.actionView is SearchView)
        Assert.assertNotNull("Search item is null", searchItem)
        Assert.assertNotNull("Menu is null", Shadows.shadowOf(activity1).optionsMenu)
    }
}