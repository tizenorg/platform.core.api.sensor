Name:       capi-system-sensor
Summary:    A Sensor library in TIZEN C API
Version:    0.1.17
Release:    0
Group:      framework/system
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
Source1001:     capi-system-sensor.manifest
BuildRequires:  cmake
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(sensor)
BuildRequires:  pkgconfig(capi-base-common)

%description
%{summary}

%package devel
Summary:  A Sensor library in TIZEN C API (Development)
Group:    framework/system
Requires: %{name} = %{version}-%{release}

%description devel
%{summary}


%prep
%setup -q
cp %{SOURCE1001} .


%build
MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`

%cmake \
  . \
  -DFULLVER=%{version} -DMAJORVER=${MAJORVER} -DVERSION="%{version}"

%__make %{?jobs:-j%jobs}


%install
%make_install

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%manifest %{name}.manifest
%license LICENSE
%{_libdir}/libcapi-system-sensor.so.*

%files devel
%manifest %{name}.manifest
%license LICENSE
%{_includedir}/system/sensors.h
%{_libdir}/pkgconfig/*.pc
%{_libdir}/libcapi-system-sensor.so
