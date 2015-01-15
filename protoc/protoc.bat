REM @echo off

protoc --cpp_out=..\project\protocol inc.proto
protoc --cpp_out=..\project\protocol csid.proto
protoc --cpp_out=..\project\protocol game.proto

pause
