FROM node
WORKDIR /usr/src/app
COPY package*.json ./
COPY index.js ./
RUN npm install
EXPOSE 8080
CMD [ "node", "index.js" ]
