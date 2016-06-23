Name:       capi-system-sensor
Summary:    A Sensor library in TIZEN C API
Version:    0.2.2
Release:    0
Group:      System/API
License:    Apache-2.0 and PD
Source0:    %{name}-%{version}.tar.gz

BuildRequires:  cmake
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(sensor)
BuildRequires:  pkgconfig(capi-base-common)
BuildRequires:  pkgconfig(context-common)
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig

%description
A Sensor Library in TIZEN C API package.

%package devel
Summary:  A Sensor library in TIZEN C API (Development)
Group:    System/Development
Requires: %{name} = %{version}-%{release}

%description devel
A Sensor library in TIZEN C API package (Development).
%devel_desc

%prep
%setup -q

%build
MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`
%cmake . -DFULLVER=%{version} -DMAJORVER=${MAJORVER}
%__make %{?_smp_mflags}

%install
rm -rf %{buildroot}
%make_install

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%manifest packaging/capi-system-sensor.manifest
%{_libdir}/libcapi-system-sensor.so.*
%license LICENSE.APLv2

%files devel
%manifest packaging/capi-system-sensor.manifest
%{_libdir}/libcapi-system-sensor.so
%{_libdir}/pkgconfig/*.pc
%{_includedir}/sensor/*.h
%license LICENSE.APLv2
