using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace lab1.Controllers {
    public class SearchController : Controller {
        // GET: Search
        public ActionResult Index() {
            return View();
        }

        public string NumarTelefon(string telefon) {
            if (telefon == null) {
                return "Numar invalid";
            }

            return telefon;
        }

        public string CNP(string cnp) {
            if (cnp == null) {
                return "Numar invalid";
            }

            return cnp;
        }
    }
}