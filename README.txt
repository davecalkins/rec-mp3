recmp3 is a Windows application which records audio from an external source
and writes it directly to an mp3 file using the LAME mp3 encoder.

To use recmp3, just run the executable.  Pick an output file and click the START
button to start recording.  When done, click the STOP button.

Note that this is a very rough initial release.  The input format and output
formats are hard-coded (Mono/Stereo, bitrate, quality, etc).  Also, you can't
enter mp3 ID data.  This is essentially an alpha release with very basic
functionality.  A more complete feature set will be added in the future.

You'll need to use the Windows Volume control application and select the correct
input channel to be used for recording (Options -> Properties -> Adjust Volume
for Recording, enable channels you want to be able to pick from, click ok, then
select the input channel you want).  Note that you can select "What U Hear" as
an input channel, which will result in anything you can hear coming from your
system being recorded.

The prod directory contains the latest distro of LAME and NASM which recmp3
depends on (LAME for the mp3 encoding and NASM to build the LAME liblamemp3.lib
static library).

recmp3 was built using MS Visual C++ v6.0.

To build recmp3, you'll first need to build libmp3lame.lib which gets statically
linked into recmp3.  To do this, you need the NASM assembler.  Although both
the NASM source and Win32 binaries are included in the prod directory, it'd
be easiest to simply copy the binaries somewhere and add them to the Visual C++
executable directory list (under options -> directories).  Once you've done that,
you can open the libmp3lame Visual Studio project and build it.  You then
add the LAME include directory and directory where the liblamemp3.lib was
generated to the Visual Studio include and lib directory lists.  This allows
Visual Studio to find the include file and library for compilation and linking.
Once you've done all this, you should be able to open the recmp3 workspace
and build recmp3.

Links:
	recmp3 SourceForge project page
		http://www.sourceforge.net/projects/recmp3
	LAME mp3 encoder home page
		http://lame.sourceforge.net
	NASM home page
		http://nasm.sourceforge.net


********************************************************************************
REVISION HISTORY
--------------------------------------------------------------------------------
2003-09-17	initial release
********************************************************************************
