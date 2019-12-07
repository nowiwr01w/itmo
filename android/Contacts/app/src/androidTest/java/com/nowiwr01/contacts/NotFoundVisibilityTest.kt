package com.nowiwr01.contacts

import androidx.test.core.app.ActivityScenario
import androidx.test.espresso.Espresso.onView
import androidx.test.espresso.action.ViewActions.click
import androidx.test.espresso.action.ViewActions.typeText
import androidx.test.espresso.assertion.ViewAssertions
import androidx.test.espresso.matcher.ViewMatchers.isDisplayed
import androidx.test.espresso.matcher.ViewMatchers.withId
import androidx.test.filters.LargeTest
import androidx.test.rule.GrantPermissionRule
import androidx.test.runner.AndroidJUnit4
import com.nowiwr01.contacts.view.MainActivity
import junit.framework.Assert.assertNotNull
import org.hamcrest.CoreMatchers
import org.junit.Before
import org.junit.Rule
import org.junit.Test
import org.junit.runner.RunWith

@Suppress("DEPRECATION")
@RunWith(AndroidJUnit4::class)
@LargeTest
class NotFoundVisibilityTest {

    @get:Rule
    var permissionSMSRule = GrantPermissionRule.grant(android.Manifest.permission.SEND_SMS)!!

    @get:Rule
    var permissionContactsRule = GrantPermissionRule.grant(android.Manifest.permission.READ_CONTACTS)!!

    @Before
    fun setUp() {
        ActivityScenario.launch(MainActivity::class.java)
    }

    @Test
    fun existingElementTest() {
        onView(withId(R.id.search))
        assertNotNull(onView(withId(androidx.appcompat.R.id.search_src_text)))
        onView(withId(R.id.search)).perform(click())
        onView(withId(androidx.appcompat.R.id.search_src_text)).perform(typeText("Test"))
        onView(withId(R.id.imgNotFound)).check(ViewAssertions.matches(CoreMatchers.not(isDisplayed())))
    }

    @Test
    fun wrongElementTest() {
        onView(withId(R.id.search))
        assertNotNull(onView(withId(androidx.appcompat.R.id.search_src_text)))
        onView(withId(R.id.search)).perform(click())
        onView(withId(androidx.appcompat.R.id.search_src_text)).perform(typeText("Teeee"))
        onView(withId(R.id.imgNotFound)).check(ViewAssertions.matches(isDisplayed()))
    }
}