#
# Copyright (C) 2022 Michael Kondrashin — All Rights Reserved
# You may use, distribute and modify this code under the
# terms of the MIT license.
# You should have received a copy of the MIT license with
# this file. If not, please write to: mkondrashin@gmail.com
#
# Lates version of this file can be found at following URL:
# https://github.com/mpkondrashin/periculosum
#
# fix_aslr.ps1 - fix ASLR for Windows platform
# 
# https://stackoverflow.com/questions/8107319/cygwin-git-error-cygheap-base-mismatch-detected
#

Get-Item -Path "C:\Program Files\Git\usr\bin\*.exe" | %{ Set-ProcessMitigation -Name $_.Name -Disable ForceRelocateImages }
