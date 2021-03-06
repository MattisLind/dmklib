# dmklib
dmklib is a library to manipulate DMK disk image files. This is NOT work by me. I did some small changes that I wanted to keep track off so that it is not getting lost.

dmklib README
$Id: README 41 2003-12-21 23:48:14Z eric $
Copyright 2002 Eric Smith <eric@brouhaha.com>

dmklib is a library to read and write DMK format floppy disk images.
DMK format was developed by David Keil to represent floppy disk images
for use in TRS-80 simulators, and has since been adopted by other software
such as xtrs by Tim Mann and M.E.S.S.  The specifications for the DMK image
file format are available on the web:

    http://discover-net.net/~dmkeil/trs80/trstech.htm#Technical-DMK-disks

dmklib is supplied with several utility/demo programs for Linux:

    rfloppy:  read an actual floppy diskette and produce a DMK image

    dmkformat:  produce a blank formatted DMK image

    dmk2raw:  extract the data from a DMK image into a raw file

    dumpids:  read and display the sector IDs from an actual floppy diskette

dmklib and the utility/demo programs are in an *extremely* crude
state, however, they have been used successfully to read 8-inch single
and double sided, single and double density floppies.  Although some
versions have been used in the past to read 5.25-inch floppies, it is
not known whether this release will do so.  Since there has been quite
a bit of interest recently on the CCTalk mailing list in Linux
software to read floppy diskettes, I have decided to make this
prerelease available now rather than wait until I've cleaned
everything up.

Further development of dmklib will be hosted on SourceForge:

    http://sf.net/projects/dmklib/

Eric Smith
19-Oct-2002


This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License version 2 as
published by the Free Software Foundation.  Note that permission is
not granted to redistribute this program under the terms of any
other version of the General Public License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111  USA

