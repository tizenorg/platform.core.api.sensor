Name:       capi-system-sensor
Summary:    A Sensor library in TIZEN C API
Version:    0.1.0
Release:    0
Group:      System/API
License:    Apache 2.0
Source0:    %{name}-%{version}.tar.gz
Source1:    capi-system-sensor.manifest

BuildRequires:  cmake
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(sensor)
BuildRequires:  pkgconfig(capi-base-common)
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
cp %{SOURCE1} .
MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`
%cmake . -DFULLVER=%{version} -DMAJORVER=${MAJORVER}
%__make %{?_smp_mflags}

%install
rm -rf %{buildroot}
%make_install

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%manifest capi-system-sensor.manifest
%{_libdir}/libcapi-system-sensor.so.*
%license LICENSE.APLv2

%files devel
%{_includedir}/sensor/*.h
%{_libdir}/pkgconfig/*.pc
%{_libdir}/libcapi-system-sensor.so

