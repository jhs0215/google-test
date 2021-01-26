# google-test
google test sample

# 개발 환경
 - Window 10 Pro x64 KR
 - Visual Studio Professional 2017 
 - Debug, Release | win32, x64

# GTEST LIB/DLL 빌드 방법
- https://github.com/google/googletest 에서 소스 경로를 받아온다.
- local 저장소에 clone
- Cmake 실행 > Browse Source 클릭 > local 저장소에서 googletest 폴더 선택
 : Browse Build 클릭 > local 저장소와 동등한 레벨의 폴더 생성 후 선택 (win32/x64)
    - Configure 클릭 > visual studio 15 2017 선택 > optional > win32/x64 선택 > BUILD_SHARED_LIBS 선택 (Runtime Library 시에 MD 옵션을 사용하기 위해, 선택 하지 않으면 MT 옵션을 이용해야 한다. ) 
    - Project 적용 후에도 전처리기 등록을 해야한다. 
https://github.com/google/googletest/blob/master/googletest/include/gtest/internal/gtest-port.h
 - Generate 클릭 > Open Project 클릭 > Debug/Release 빌드
-  필요한 파일 추출 (DLL/LIB/INCLUDE)
    - include : local 저장소 > googletest > include 
    - lib : win32/x64 프로젝트 경로 > lib > debug/release > gtest.lib, gtest_main.lib ( debug 의 경우 name 뒤에 d 가 붙는다. )
    - dll : win32/x64 프로젝트 경로 > bin > debug/release > gtest.dll, gtest_main.dll

# PROJECT 적용 방법
- MFC 대화상자 기반 샘플 솔루션을 만든다. 
- 솔루션 탐색기 > 솔루션 마우스 우클릭 > 추가 > 새 프로젝트 > Windows 데스크톱 > Windows 콘솔 응용 프로그램 생성
- local 저장소에서 솔루션 위치의 상위에 (솔루션 기준 : .\..\, gtest 프로젝트 기준 : .\..\..\) include 폴더와 lib 폴더를 생성 후 build condition 에 맞게 dll, lib, header 복사 
    - gtest 프로젝트 기준으로 Debug|x86 적용시 다음과 같은 경로이다.  
        include : .\..\..\include   
        lib : .\..\..\lib  
        dll : .\Debug   
# gtest 프로젝트 설정
- 솔루션 탐색기 > gtest 프로젝트 마우스 우클릭 > 속성 > c/c++ 과 링커에 lib/include 적
    - include : 구성속성 > c/c++ > 일반 > 추가 포함 디렉터리 > ..\..\include 추가
    - lib :   
        구성속성 > 링커 > 일반 > 추가 라이브러리 디렉터리 > ..\..\lib 추가  
        구성속성 > 링커 > 입력 > 추가 종속성 > gtestd.lib, gtest_maind.lib 추가  
    - 전처리기 : GTEST_LINKED_AS_SHARED_LIBRARY=1 입력 - 
- 솔루션 탐색기 > gtest 프로젝트 마우스 우클릭 > 속성 > 구성 속성 > 일반 > MFC 사용을 공유 dll 에서 MFC 사용으로 변경
- gtest 전역 설정
    - header 추가  
        pch.h > #include <gtest\gtest.h> 추가  
        pch.h > #include <afxwin.h> 추가  
- main 함수 수정
    - argc, argv 를 매개변수로 전달 받는다
    - AfxWinInit 를 이용하여 window 를 초기화 한다.
    - ::testing::InitGoogleTest 를 이용해서 테스트 설정을 초기화 한다.
    - RUN_ALL_TESTS 를 이용하여 모든 테스트를 실행한다.
- gtest 를 시작 프로젝트로 설정 후 디버그 실행

# 참고
 - google test 문법과 관련된 사항은 https://github.com/google/googletest/blob/master/googletest/docs/primer.md 을 참고하면 된다.

 

