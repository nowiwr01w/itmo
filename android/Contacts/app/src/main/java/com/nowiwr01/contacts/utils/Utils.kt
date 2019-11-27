package com.nowiwr01.contacts.utils

import com.nowiwr01.contacts.model.Contact
import kotlin.random.Random

object Utils {

    private fun initialize() : MutableList<Contact> {
        val contactList = mutableListOf<Contact>()
        for (i in 0..0) {
            contactList.add(
                Contact(names[Random.nextInt(names.size)],
                phones[Random.nextInt(phones.size)], images[Random.nextInt(images.size)])
            )
        }
        return contactList
    }

    // If you don't know how to get access to contact list, just use it

    val images = listOf(
        "boy", "boy1", "girl", "girl1", "man", "man1", "man2", "man3", "man4"
    )

    private val names = listOf(
        "Joe", "Mark", "Din", "Andrey", "Maria", "Anton", "Alex", "Jem", "Karl", "Edgard"
    )

    private val phones = listOf(
        "+7 951 685-63-28", "+7 951 667-13-80", "+7 950 656-56-51", "+7 950 631-27-68",
        "+7 950 194-42-51", "+7 929 929-25-71", "+7 905 540-51-24", "+7 951 680-63-15",
        "+38 093 035-81-24"
    )

//    val contactList = initialize()
}