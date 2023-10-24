# Readme

세부적인 구현 내용은 subdirectory에 위치한 여러 문서들을 참조하시기 바랍니다.

## Development method

### Branch

GitHub에 Branch 관리 방법으로 [Trunk Based Development](https://trunkbaseddevelopment.com/)를 적용하고자 합니다. [적절한 한국어 블로그의 설명](https://tech.mfort.co.kr/blog/2022-08-05-trunk-based-development/)도 읽어보시면 도움이 될 듯 합니다. 적당히 main branch가 혼잡하지 않게 하는 것이 목적이기에 엄격하게 적용하지 않으니 적당히 적용하시면 됩니다.

Git에 대한 설명은 다음 [Pro Git](https://git-scm.com/book/ko/v2) 문서를 참조하시면 됩니다. 정 모르시겠다면 제 이메일로 코드를 보내주시면 제가 commit하도록 하겠습니다.

### Issue

Github는 내장 issue tracker를 지원하며, 우리 repo의 issue tracker는 [다음 링크](https://github.com/pinipaper/embedded-system-design/issues)에서 확인하실 수 있습니다. 적절히 개발해야 할 내용을 고민 후, 기능 단위로 쪼개서 issue를 제시합니다. New Issue를 누르시면 우측에 어느 분에게 이 Issue를 할당할 지, 어떤 Label이 들어갈 지 정하실 수 있습니다. Development에서는 이 issue에 해당하는 branch를 생성할 수 있으니 적극 활용하시기 바랍니다.

### Commit

commit을 하려할 때 commit message를 입력하여야 합니다. message의 구성은 다음처럼 작성하면 됩니다. 제목은 간결하게, 본문은 개조식으로 짧게 기입하시면 됩니다.

```
태그: 제목

본문
```

#### Tag

본인이 작업한 내용에 따라 적절한 Tag를 붙여주시기 바랍니다.

| **Tag**  | **Description** |
|---|---|
| feat | 기능 추가 |
| bugfix | 버그 수정 |
| doc | 문서 추가, 수정, 삭제 |
| chore | 기타 등등 |

#### Example

```
doc: ESP32 설명 추가

- ESP32 Deep Learning Toolbox 내용 추가
- ESP32 ML example 추가
```

