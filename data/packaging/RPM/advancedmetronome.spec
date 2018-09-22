Name:			advancedmetronome
Version:		1.0
Release:		1%{dist}
Summary:		Advanced Metronome is a small application in which you can set multiple measures.
Group:			Multimedia

License:		GPLv3+
URL:			https://github.com/bartkessels/%{name}
Source0:		https://github.com/bartkessels/%{name}/archive/%{version}/%{name}-%{version}.tar.gz

BuildRequires:	gcc
BuildRequires:	gcc-c++
BuildRequires:	make
BuildRequires:	qt5-devel
BuildRequires:	qt5-qtbase-devel
BuildRequires:	qt5-qtmultimedia-devel

Requires:		qt5-qtbase
Requires:		qt5-qtmultimedia

%description
Advanced Metronome is created for musicians who want to practice songs which have multiple
speeds and/or time-durations. 'Cause regular metronomes only allow one constant tempo Advanced Metronome
steps in to solve this problem.

Advanced Metronome also gives you the ability to save and share your songs with other so this application will
suit many bands in their song-writing process.

%global debug_package %{nil}

%prep
%autosetup

%build
qmake-qt5 PREFIX=%{_prefix}
make %{?_smp_mflags}

%install
export INSTALL_ROOT=%{buildroot}
make install

%files
%{_bindir}/advancedmetronome
%{_datarootdir}/net.bartkessels.advancedmetronome/translations/*
%{_datarootdir}/appdata/net.bartkessels.advancedmetronome.appdata.xml
%{_datarootdir}/applications/net.bartkessels.advancedmetronome.desktop
%{_datarootdir}/icons/hicolor/*/apps/net.bartkessels.advancedmetronome*.*

%changelog
* Sat Sep 22 2018 Bart Kessels <bartkessels@bk-mail.com> 1.0
- Initial Release
