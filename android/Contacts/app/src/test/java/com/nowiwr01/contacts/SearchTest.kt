package com.nowiwr01.contacts

import androidx.test.rule.ActivityTestRule
import com.nowiwr01.contacts.adapters.ContactAdapter
import com.nowiwr01.contacts.view.MainActivity
import com.nowiwr01.contacts.model.Contact
import org.junit.Assert
import org.junit.Assert.assertEquals
import org.junit.Rule
import org.junit.Test
import org.junit.runner.RunWith
import org.robolectric.RobolectricTestRunner

@RunWith(RobolectricTestRunner::class)
class SearchTest {

    private val contacts = arrayListOf(
        Contact("Andrey Default", "+79516856328", "man"),
        Contact("Andrey New", "+79216583412", "man1"),
        Contact("Andrey Old", "+79516806315", "man2"),
        Contact("Varya", "+79516671380", "girl"),
        Contact("Varya", "+380996639599", "girl2"),
        Contact("Mom", "+79506312768", "girl1"),
        Contact("Dad", "+79501944251", "man3")
    )

    private val filter = ContactAdapter.SearchFilter(contacts) {}

    private fun search(sequence: CharSequence?) = filter.filterResults(sequence)

    @get:Rule
    val activityRule = ActivityTestRule(MainActivity::class.java)

    @Test
    fun searchByNameTest(){
        assertEquals(contacts, search(""))
        assertEquals(arrayListOf(contacts[5]), search("OM"))
        assertEquals(arrayListOf(contacts[3], contacts[4]), search("  VaRyA "))
        assertEquals(arrayListOf(contacts[0], contacts[1], contacts[2]), search("And"))
    }

    @Test
    fun searchByNPhoneTest(){
        assertEquals(contacts, search(""))
        assertEquals(arrayListOf<Contact>(), search("8950"))
        assertEquals(arrayListOf(contacts[6]), search("251"))
        assertEquals(arrayListOf(contacts[4]), search("966"))
        assertEquals(arrayListOf(contacts[0], contacts[2], contacts[3]), search("+7951"))
    }

    @Test
    fun searchByFullNameOrPhone() {
        assertEquals(arrayListOf<Contact>(), search("+79500000000"))
        assertEquals(arrayListOf(contacts[4]), search("+380996639599"))
        assertEquals(arrayListOf(contacts[0]), search("Andrey Default"))
    }
}