using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace lab1.Controllers {
    public class StudentController : Controller {
        // GET: Student
        public string Index() {
            return "Lista tuturor studentilor.";
        }

        public string Create() {
            return "Student nou creat";
        }
        
        public string Read(int id) {
            return "Student cu IDul " + id;
        }

        public string Update(int id) {
            return "Pagina de edit a studentului cu IDul " + id;
        }

        public string Delete(int id) {
            return "Stergem studentul cu IDul " + id;
        }
    }
}