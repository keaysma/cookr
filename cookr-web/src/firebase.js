// src/firebase.js
import firebase from 'firebase'
const firebaseConfig = {
    apiKey: "AIzaSyDcKuBrQYZkcMYpTcqjXb6c70HzV4uhPZg",
    authDomain: "cookr-bd872.firebaseapp.com",
    databaseURL: "https://cookr-bd872-default-rtdb.firebaseio.com",
    projectId: "cookr-bd872",
    storageBucket: "cookr-bd872.appspot.com",
    messagingSenderId: "1088633266852",
    appId: "1:1088633266852:web:7ddba0d1d3b4a29199bc31",
    measurementId: "G-KM49XE8XEM"
}
firebase.initializeApp(firebaseConfig)

export const provider = new firebase.auth.GoogleAuthProvider()
export const auth = firebase.auth()
export default firebase