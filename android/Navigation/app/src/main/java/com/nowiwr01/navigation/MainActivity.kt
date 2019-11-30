package com.nowiwr01.navigation

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import androidx.fragment.app.Fragment
import androidx.fragment.app.FragmentManager
import com.google.android.material.tabs.TabLayout
import com.nowiwr01.navigation.fragments.RootFragment
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        toolbar.navigationIcon = resources.getDrawable(R.drawable.ic_back)
        toolbar.setNavigationOnClickListener {
            onBackPressed()
        }

        if (savedInstanceState == null) {
            switchTab(TAG_PROFILE)
        } else {
            val curState = getTabTag(savedInstanceState.getInt(TAB_STATE))
            reselectTabs(curState)
            getLastChild(curState)
        }

        bottomNavigation.addOnTabSelectedListener(object : TabLayout.OnTabSelectedListener {
            override fun onTabReselected(tab: TabLayout.Tab?) {
                // тык сюда же
                getLastChild(getTabTag(tab!!.position))
            }

            override fun onTabUnselected(tab: TabLayout.Tab?) {
                // уходим с этого таба
                hidePage(getTabTag(tab!!.position))
            }

            override fun onTabSelected(tab: TabLayout.Tab?) {
                // перешли на другой
                switchTab(getTabTag(tab!!.position))
            }
        })
    }

    override fun onSaveInstanceState(outState: Bundle) {
        super.onSaveInstanceState(outState)
        outState.putInt(TAB_STATE, bottomNavigation.selectedTabPosition)
    }

    override fun onBackPressed() {
        if (supportFragmentManager.backStackEntryCount > 0) {
            val currentTag = getTabTag(bottomNavigation.selectedTabPosition)
            val currentRoot = getRootFragment(currentTag)
            if (currentRoot != null) {
                currentRoot.childFragmentManager.popBackStackImmediate()
                if (currentRoot.childFragmentManager.backStackEntryCount == 0) {
                    currentRoot.fragmentManager?.popBackStackImmediate(currentTag,
                        FragmentManager.POP_BACK_STACK_INCLUSIVE
                    )
                    val lastTag = getLastBackStackTag()
                    if (lastTag != TAG_NO && lastTag != null) {
                        switchTab(lastTag)
                    } else {
                        finish()
                    }
                }
            }
        }
    }

    private fun getLastBackStackTag(): String? {
        if (supportFragmentManager.backStackEntryCount == 0) {
            return TAG_NO
        } else {
            val lastTag = supportFragmentManager
                .getBackStackEntryAt(supportFragmentManager.backStackEntryCount - 1).name ?: return TAG_NO
            return if (supportFragmentManager.findFragmentByTag(lastTag)?.childFragmentManager!!.backStackEntryCount == 0) {
                supportFragmentManager.popBackStackImmediate(lastTag,
                    FragmentManager.POP_BACK_STACK_INCLUSIVE
                )
                getLastBackStackTag()
            } else {
                lastTag
            }
        }
    }

    private fun getRootFragment(tab: String): Fragment? {
        return supportFragmentManager.findFragmentByTag(tab)
    }

    private fun switchTab(tag: String) {
        showPage(tag)
        reselectTabs(tag)
    }

    private fun showPage(tag: String) {
        toolbar.title = getTitle(tag)
        if (getRootFragment(tag) == null || getRootFragment(tag)!!.childFragmentManager.backStackEntryCount == 0) {
            val newRoot = RootFragment()
            supportFragmentManager
                .beginTransaction()
                .add(R.id.fragment_container, newRoot, tag)
                .addToBackStack(tag)
                .commit()
            supportFragmentManager.executePendingTransactions()
            newRoot.addFirstChild()
        } else {
            getRootFragment(tag)?.apply {
                supportFragmentManager.beginTransaction().addToBackStack(tag).show(this).commit()
                getLastChild(tag)
            }
        }
    }

    private fun getLastChild(tag: String) {
        getRootFragment(tag)?.apply {
            val latestChild = childFragmentManager.findFragmentByTag(tag)
            if (latestChild != null) {
                childFragmentManager.beginTransaction().show(latestChild).commitNow()
            }
        }
    }

    private fun reselectTabs(tab: String) {
        val position = getTabPosition(tab)
        for (i in 0 until 3) {
            bottomNavigation.getTabAt(i)?.apply {
                if (i == position) {
                    select()
                }
            }
        }
    }

    private fun hidePage(tag: String) {
        getRootFragment(tag)?.apply {
            val latestChild = childFragmentManager.findFragmentByTag(tag)
            if (latestChild != null) {
                childFragmentManager.beginTransaction().hide(latestChild).commitNow()
            }
        }
    }

    private fun getTabTag(position: Int) = when (position) {
        0 -> TAG_PROFILE
        1 -> TAG_CHAPTER
        2 -> TAG_STORE
        else -> TAG_NO
    }

    private fun getTabPosition(tag: String): Int {
        return when (tag) {
            TAG_PROFILE -> 0
            TAG_CHAPTER -> 1
            TAG_STORE -> 2
            else -> 0
        }
    }

    private fun getTitle(tag: String) : String {
        return when (tag) {
            TAG_PROFILE -> "Profile"
            TAG_CHAPTER -> "Chapter"
            TAG_STORE -> "Store"
            else -> "NO TAB?"
        }
    }

    companion object {
        const val TAG_NO = "none"
        const val TAB_STATE = "tab"

        const val TAG_PROFILE = "profile"
        const val TAG_CHAPTER = "chapter"
        const val TAG_STORE = "store"
    }
}
