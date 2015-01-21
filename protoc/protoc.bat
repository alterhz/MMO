REM @echo off

protoc --cpp_out=..\project\protocol inc.proto
protoc --cpp_out=..\project\protocol csid.proto
protoc --cpp_out=..\project\protocol msg.proto
protoc --cpp_out=..\project\protocol scsid.proto
protoc --cpp_out=..\project\protocol smsg.proto
pause
