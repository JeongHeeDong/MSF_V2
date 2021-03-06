# SFTPCollector

**Remote files -> (SFTP) -> local, STDOUT**

1. 원격 서버에 SFTP 프로토콜로 연결하여 sleep_time 마다 설정된 remote_dir을 감시한다.
2. 파일이름의 끝이 remote_patt 패턴과 일치하는 파일이 확인될 경우 local_dir안에 해당 파일을 다운로드 하고 다운로드 된 경로를 STDOUT으로 출력한다.
3. index 기능이 있으며 index를 통해 파일을 어디까지 감시했는지 확인하여 중복되는 파일은 가져오지 않는다.

## How to use
```Bash
$ python [File] [Section] [Config path] [--help] [--stime|--etime] (year/month/day/hour/minute)
```
- Section : 실행할 Config의 섹션
- Config path : 실행할 Config의 경로
- --help : usage 정보
- --stime : stime 이상의 시간에 생성및 수정된 파일들을 감시한다.
- --etime : etime 이하의 시간에 생성및 수정된 파일들만 감시한다.

## STDIN
없음

## STDOUT
```Bash
file://<저장된 파일 경로>
```

## Configuration

**ColSFTP.conf**

|Section |Option      |Range      |Description                                       |
|:------:|:----------:|-----------|--------------------------------------------------|
|Log     | log_path   | (string)  | log가 저장될 경로                                |
|        | log_size   | (int)     | log파일의 최대 사이즈                            |
|        | log_count  | (int)     | log파일의 최대 수                                |
|Section | ftp_ip     | (string)  | 접속할 ftp host 주소                             |
|        | ftp_port   | (string)  | 접속할 ftp port                                  |
|        | ftp_id     | (string)  | 접속할 ftp id                                    |
|        | ftp_pwd1   | (string)  | 접속할 ftp password1                             |
|        | ftp_pwd2   | (string)  | 접속할 ftp password2(보안상 두개 이용)           |
|        | remote_dir | (string)  | 감시할 원격호스트의 디렉토리 경로                |
|        | remote_patt| (string)  | 감시할 원격호스트의 디렉토리 안의 파일이름 패턴  |
|        | local_dir  | (string)  | 다운로드한 파일이 저장될 로컬호스트의 경로       |
|        | index_path | (string)  | Index경로                                        |
|        | index_name | (string)  | Index이름                                        |
|        | sleep_time | (string)  | FTP가 감시할 시간 설정                           |
|        | pathsidx   | (string)  | 원격지의 경로에서 가져다 쓸 경로 시작 인덱스     |
|        | patheidx   | (string)  | 원격지의 경로에서 가져다 쓸 경로 끝 인덱스       |

## Prerequisites
- Python == 2.7
- Paramiko >= 2.4.1

## How to unit test (Dynamic test)
```Bash
$ nosetests -v --with-coverage --with-doctest --cover-erase --exe  --cover-package=. tests/*.py
```

## How to lint test (Static test)
```Bash
$ pylint --disable=C --disable=E0602 --msg-template='{path}:{line}:[{msg_id}({symbol}),{obj}]{msg}' *.py
```

## Example
1. 우선 index, data, tmp 세 디렉토리의 안을 비워줍시다.
2. example.sh를 실행시키면 10개의 파일이 각각 Config에 지정한 디렉토리에 1초마다 생기고 해당 모듈이 Config에 지정된 시간(현재 5초)마다 감시된 파일을 STDOUT으로 출력하는 것을 볼 수 있습니다.
3. 그리고 감시된 파일은 Config에 지정된 디렉토리(현재 tmp)로 받아오는걸 확인 할 수 있습니다.
3. 마지막으로 log와 index를 확인하세요.
