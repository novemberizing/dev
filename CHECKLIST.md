### CHECKLIST

#### GITHUB PROJECT

| Action item                      | Target | Description |
| -------------------------------- | ------ | ----------- |
| Create a github repository       | github | ...         |
| Update github repository's about | github | ...         |
| Enable github pages              | github | ...         |
| git config user name and email   | shell  | ...         |
| Create docs/index.html           | editor | ...         |

#### STATIC WEBSITE (AWS)

| Action item                      | Target | Description |
| -------------------------------- | ------ | ----------- |
| AWS Select region                | AWS    | ...         |
| Create ec2 instance              | AWS    | ...         |
| Manage secret key                | AWS    | ...         |
| Add network security rule        | AWS    | ...         |
| Elastic IP                       | AWS    | ...         |
| Setting SSH Agent                | SSH    | ...         |
| ssh keygen for service           | SHELL  | https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent |
| register generated key in github | GITHUB | ...         |
| git clone project in home's workspace | SHELL | ... |
| docker install                   | SHELL  | https://docs.docker.com/engine/install/ubuntu/ |
| nginx install                    | SHELL  | https://www.nginx.com/resources/wiki/start/topics/tutorials/install/ |
| nginx configure for static web   | SHELL  | `/etc/nginx/sites-available/default` |
| nginx configure for permission   | SHELL  | ... |
| dns setting                      | DNS | ... |
| SSL Setting (Let's encrypt)      | SHELL | https://nginxstore.com/blog/nginx/lets-encrypt-%EC%9D%B8%EC%A6%9D%EC%84%9C%EB%A1%9C-nginx-ssl-%EC%84%A4%EC%A0%95%ED%95%98%EA%B8%B0/ |
| Check connectivity               | BROWSER | ... |

https://nginxstore.com/blog/nginx/lets-encrypt-%EC%9D%B8%EC%A6%9D%EC%84%9C%EB%A1%9C-nginx-ssl-%EC%84%A4%EC%A0%95%ED%95%98%EA%B8%B0/



https://baengsu.tistory.com/24
https://stackoverflow.com/a/43686446

```sh
sudo chcon -R -t httpd_sys_content_t /home/ubuntu
```

```sh
# Add your user to the docker group.
sudo usermod -aG www-data $USER
newgrp www-data
```

https://www.ralfebert.com/tutorials/nginx-static-website-with-https/
https://ganbarujoy.tistory.com/113

#### STATIC WEBSITE (GITHUB PAGES)

| Action item                      | Target | Description |
| -------------------------------- | ------ | ----------- |
| ...                              | ...    | ...         |

#### MYSQL INSTALL

| Action item                      | Target | Description |
| -------------------------------- | ------ | ----------- |
| ...                              | ...    | ...         |

### 서비스를 만들기 위한 체크리스트

| Action item                      | Target | Description |
| -------------------------------- | ------ | ----------- |
| 개인정보처리방침만들기             | ...    | ...         |
| 이용약관 만들기                   | ...    | ...         |