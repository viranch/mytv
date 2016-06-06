mytv
=========

A minimal system tray context menu based TV shows updater based on user-specified RSS feed, best suited for Mac OS menubar but is cross platform. Backed by [FollowShows](http://followshows.com), [Torrentz](https://torrentz.com) and [Torcache](https://torcache.net).

Install
---------

### Qt 5.x Dependency

This application is built using Qt 5.x, so you would need to have this before you can compile the source code.

Check the version with:

    qmake -v

Look at the version of Qt libraries, not the version of `qmake` itself. Install relevant package if you don't have the `qmake` command.

### Build

Following applies to Linux only; for MacOS build, check the [releases](https://github.com/viranch/mytv/releases) section.

Download and compile:

    git clone git://github.com/viranch/mytv.git
    cd mytv
    mkdir build && cd build
    qmake ..
    make

Run:

    ./mytv

Optionally, install to `/usr/bin`:

    sudo cp build/mytv /usr/bin/mytv

Use
---------

1. Sign up on [FollowShows](http://followshows.com/) and follow your favourite shows.
2. Set the link to RSS feed from your account in settings of this app.
3. The app will periodically look for new episodes from the feed and update with search results from [Torrentz](https://torrentz.com/)
4. Copy the link for .torrent to clipboard with a single click and use it in your torrent client.
5. Add the download directly to a [Transmission](http://transmissionbt.com/) daemon running locally (enable remote access) or remotely with a single click, you need to add the backend in settings.
